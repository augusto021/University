import re

file_path = "./markdown_file.md"

with open(file_path,'r') as file:
    text = file.read()


patterns = [
    # Heading
    (r'^# (.+)$',r'<h1>\1</h1>'),
    (r'^## (.+)$',r'<h2>\1</h2>'),
    (r'^### (.+)$',r'<h3>\1</h3>'),
    # Bold
    (r'\*\*(.+)\*\*',r'<b>\1</b>'),
    # Italic
    (r'\*(.+)\*',r'<i>\1</i>'),
    # Ordered List
    (r'^\d\. (.+)$',r'<li>\1</li>'),
    # Link
    (r'\[(.+)\]\((.+)\)',r'<a href="\2">\1</a>'),
    # Image
    (r'\!\[(.+)\]\((.+)\)',r'<img src="\2" alt="\1"/>')
]

def new_pattern(text, patterns):
    for pattern, replacement in patterns:
        text = re.sub(pattern, replacement, text, flags=re.MULTILINE)
    return text


# add <ol> and </ol> tags
lines = new_pattern(text, patterns).split('\n')
inside_ol = False

for i, line in enumerate(lines):
    line = line.strip()
    
    if line.startswith('<li>'):
        if not inside_ol:
            lines[i] = '<ol>\n' + line
            inside_ol = True
    
    elif inside_ol and not line.startswith('<li>'):
        lines[i-1] += '\n</ol>'
        inside_ol = False

if inside_ol:
    lines[-1] += '\n</ol>'


html_file = "./markdown_to_html.html"
with open(html_file,"w") as html:
    html.write('\n'.join(lines))