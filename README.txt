YAML ↔ C Header Conversion Pipeline

This project demonstrates a round-trip data conversion between YAML and C, following the RISC-V Unified Database challenge:

1. Convert a YAML file to a C header file containing key-value pairs.
2. Convert back from the generated C header to YAML.
3. Verify that the second YAML matches the first generated YAML.

---

Folder Structure

project_root/
│
├── input_yamls/       # Original YAML files
├── output_yamls/      # Generated YAML files
├── gen_c_header.py    # Python script: YAML → C header
├── gen_yaml.c         # C program: C header → YAML
├── parsed.h           # Generated C header (output of step 1)
└── readme.txt

---

Prerequisites

* Python 3.x
* GCC (or any C compiler)
* PyYAML (for YAML parsing in Python)

Install PyYAML if not already installed:

pip install pyyaml

---

Usage

1. Generate C Header from YAML

python3 gen_c_header.py ./input_yamls/dpc.yaml

Example output:

[OK] Generated C header: parsed.h

2. Compile C Program for Reverse Conversion

gcc gen_yaml.c -o gen_yaml

3. Generate YAML from C Header

./gen_yaml > ./output_yamls/result.yaml

Example output:

[OK] Generated YAML from C header.

---

Example Full Run

sagar@Sagar:~/RISCV$ python3 gen_c_header.py ./input_yamls/dpc.yaml
[OK] Generated C header: parsed.h

sagar@Sagar:~/RISCV$ gcc gen_yaml.c -o a.out

sagar@Sagar:~/RISCV$ ./a.out > ./output_yamls/result.yaml
[OK] Generated YAML from C header.

---

Notes

* The generated .h file is safe for C compilers (all newlines escaped as \n).
* Output YAML may not exactly match the original input but will be consistent after a second round-trip.
* To test full round-trip integrity, feed output_yamls/result.yaml back into gen_c_header.py and repeat.

---

Process Diagram

   ┌─────────────────┐
   │ input_yamls/    │
   │  (dpc.yaml)     │
   └───────┬─────────┘
           │
           ▼
 ┌──────────────────────┐
 │ gen_c_header.py       │
 │ (YAML → C header)     │
 └─────────┬─────────────┘
           │
           ▼
   ┌─────────────────┐
   │ parsed.h        │
   │ (C header)      │
   └───────┬─────────┘
           │
           ▼
 ┌──────────────────────┐
 │ gen_yaml.c            │
 │ (C header → YAML)     │
 └─────────┬─────────────┘
           │
           ▼
   ┌─────────────────┐
   │ output_yamls/   │
   │  (result.yaml)  │
   └─────────────────┘
