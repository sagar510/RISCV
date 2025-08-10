import yaml
import sys
from pathlib import Path 

def flatten_yaml(data, parent_key="", sep="."):
    items = []
    if isinstance(data, dict):
        for k,v in data.items():
            new_key = f"{parent_key}{sep}{k}" if parent_key else str(k)
            items.extend(flatten_yaml(v, new_key, sep=sep))
    elif isinstance(data, list):
        for i,v in enumerate(data):
            new_key = f"{parent_key}{sep}{i}"
            items.extend(flatten_yaml(v, new_key, sep=sep))
    else:
        items.append((parent_key, str(data)))
    return items

def escape_for_yaml_literal(raw):
    s = raw.replace("\\", "\\\\")
    s = s.replace("\n", "\\n")
    s = s.replace("\"", "\\\"")
    return s

def generate_c_header(flattened_items, struct_name, header_guard):
    lines = []
    lines.append(f"#ifndef {header_guard}")
    lines.append(f"#define {header_guard}")
    lines.append("")
    lines.append("typedef struct {")
    lines.append("    const char *key;")
    lines.append("    const char *value;")
    lines.append("} yaml_kv_t;")
    lines.append("")
    lines.append(f"static const yaml_kv_t {struct_name}[] = {{")
    for key, value in flattened_items:
        lines.append(f'    {{"{key}", "{value}"}},')
    lines.append("    {NULL, NULL} // terminator")
    lines.append("};")
    lines.append("")
    lines.append("#endif")
    return "\n".join(lines)

def main(yaml_path):
    yaml_file = Path(yaml_path)

    with open(yaml_file, "r", encoding="utf-8") as f :
        data = yaml.safe_load(f)

    flattened = flatten_yaml(data)

    flat_for_yaml = [(k, escape_for_yaml_literal(v)) for k, v in flattened]
    
    c_header_content = generate_c_header(flat_for_yaml, "mystruct", "parser")

    output_file = "parsed.h"
    with open(output_file, "w", encoding="utf-8") as f:
        f.write(c_header_content)
    
    print(f"[OK] Generated C header: {output_file}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} input.yaml")
        sys.exit(1)
    main(sys.argv[1])