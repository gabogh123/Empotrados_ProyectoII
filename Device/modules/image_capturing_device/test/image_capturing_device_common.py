# © 2010 Intel Corporation

import simics

# Extend this function if your device requires any additional attributes to be
# set. It is often sensible to make additional arguments to this function
# optional, and let the function create mock objects if needed.
def create_image_capturing_device(name = None):
    '''Create a new image_capturing_device object'''
    image_capturing_device = simics.pre_conf_object(name, 'image_capturing_device')
    simics.SIM_add_configuration([image_capturing_device], None)
    return simics.SIM_get_object(image_capturing_device.name)
