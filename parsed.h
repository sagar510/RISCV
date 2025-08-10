#ifndef parser
#define parser

typedef struct {
    const char *key;
    const char *value;
} yaml_kv_t;

static const yaml_kv_t mystruct[] = {
    {"$schema", "csr_schema.json#"},
    {"kind", "csr"},
    {"name", "dpc"},
    {"long_name", "Debug PC Register"},
    {"address", "1969"},
    {"priv_mode", "D"},
    {"length", "MXLEN"},
    {"writable", "True"},
    {"description", "Upon entry to debug mode, dpc is updated with the virtual address of the next instruction to be executed.\n\nExecuting the Program Buffer may cause the value of dpc to become UNSPECIFIED. If that is the case,\nit must be possible to read/write dpc using an abstract command with postexec not set. The debugger\nmust attempt to save dpc between halting and executing a Program Buffer, and then restore dpc before\nleaving Debug Mode.\n\nIf the Access Register abstract command supports reading dpc while the hart is running, then the\nvalue read should be the address of a recently executed instruction.\n\nIf the Access Register abstract command supports writing dpc while the hart is running, then the\nexecuting program should jump to the written address shortly after the write occurs.\n\nThe writability of dpc follows the same rules as mepc as defined in the Privileged Spec. In particular,\ndpc must be able to hold all valid virtual addresses and the writability of the low bits depends on\nIALIGN.\n\nWhen resuming, the hart’s PC is updated to the virtual address stored in dpc. A debugger may write\ndpc to change where the hart resumes.\n\nThis CSR is read/write.\n"},
    {"definedBy", "Sdext"},
    {"fields.DPC.location_rv32", "31-0"},
    {"fields.DPC.location_rv64", "63-0"},
    {"fields.DPC.type", "RW"},
    {"fields.DPC.description", "Debug PC Value"},
    {"fields.DPC.reset_value", "UNDEFINED_LEGAL"},
    {NULL, NULL} // terminator
};

#endif