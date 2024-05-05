#include <linux/module.h>
#include <linux/pci.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define DEVICE_NAME "pci_capture_device"
#define VENDOR_ID 0x1234
#define DEVICE_ID 0x5678

struct pci_capture_dev {
    struct cdev cdev;
    void __iomem *hw_regs;
};

static struct class *cl;
static int major;
static struct pci_capture_dev pci_dev;

static struct pci_device_id pci_ids[] = {
    { PCI_DEVICE(VENDOR_ID, DEVICE_ID), },
    { 0, }
};
MODULE_DEVICE_TABLE(pci, pci_ids);

static int pci_capture_open(struct inode *inode, struct file *file) {
    file->private_data = &pci_dev;
    return 0;
}

static ssize_t pci_capture_read(struct file *file, char __user *buffer, size_t count, loff_t *offset) {
    struct pci_capture_dev *dev = file->private_data;
    u32 file_size;
    u8 data;

    // Read the file size
    file_size = ioread32(dev->hw_regs + 0x8);

    if (*offset >= file_size) {
        return 0;
    }

    if (count > file_size - *offset) {
        count = file_size - *offset;
    }

    // Read the data chunk by chunk
    for (int i = 0; i < count; i++) {
        data = ioread8(dev->hw_regs + 0x12 + *offset + i); // Starting from Buffer0
        if (copy_to_user(buffer + i, &data, 1)) {
            return -EFAULT;
        }
    }

    *offset += count;
    return count;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = pci_capture_open,
    .read = pci_capture_read,
};

static int pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent) {
    pci_dev.hw_regs = pci_iomap(pdev, 0, pci_resource_len(pdev, 0));
    return 0;
}

static void pci_remove(struct pci_dev *pdev) {
    pci_iounmap(pdev, pci_dev.hw_regs);
}

static struct pci_driver pci_driver = {
    .name = DEVICE_NAME,
    .id_table = pci_ids,
    .probe = pci_probe,
    .remove = pci_remove,
};

static int __init pci_capture_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    cl = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(cl, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    pci_register_driver(&pci_driver);
    return 0;
}

static void __exit pci_capture_exit(void) {
    pci_unregister_driver(&pci_driver);
    device_destroy(cl, MKDEV(major, 0));
    class_destroy(cl);
    unregister_chrdev(major, DEVICE_NAME);
}

module_init(pci_capture_init);
module_exit(pci_capture_exit);

MODULE_LICENSE("GPL");

