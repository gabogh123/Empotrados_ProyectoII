# Empotrados_ProyectoII

Segundo proyecto del curso de Sistemas Empotrados del primer semestre 2024

## Project Setup

Project creation
```bash
/bin/project-setup
```
Add model to project
```bash
/bin/project-setup --device image-capturing-device --ignore-existing-files
```
Make device
```bash
make
```

## Simulation

Open simics
```bash
./simics
```

Runs simics commands and creates device on simulation
```simics
run-command-file targets/qsp-x86/icd.simics
```

