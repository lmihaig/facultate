
python ./tema1_runner.py --help pentru meniul de ajutor

python ./tema1_runner.py [OPTIONS] [TASK] [INPUT_DIR] [OUTPUT_DIR]
╭─ Arguments ───────────────────────────────────────────────────────────────────────╮
│   task            [TASK]        [default: task3]                                  │
│   input_dir       [INPUT_DIR]   [default: ../evaluare/fake_test/]                 │
│   output_dir      [OUTPUT_DIR]  [default: ./rezultate/task3/]                     │
╰───────────────────────────────────────────────────────────────────────────────────╯

exemplu:
Task 1: 
python tema1_runner.py task1 ../testare/ ./rezultate/task_1

Task 2: 
python tema1_runner.py task2 ../testare/ ./rezultate/task_2

Task 3: 
python tema1_runner.py task3 ../testare/ ./rezultate/task_3

(implementarea e la fel pt task1 task2 si task3 nu am vazut de ce sa le separ)
fisierul template_tabla.jpg si config.json sunt STRICT NECESARE (bodge) [template_tabla poate fi inlaturat daca e inlocuit cu pathul corect al unei poze cu tabla goala in config.json]
directorul extra e complet nenecesar dar are multe exemple despre cum am progresat
directorul rezultate e acolo doar sa nu faca urat la rularea cu parametrii default
fisierul DDD.py contine logica gameloopului
evalueaza_improved e o versiune mai buna a codului de evaluare, cu culori ce arata diferentele
util.py e alcatuit din toate functiile ajutatoare necesare
requirements.txt reprezinta bibliotecile necesare, se regasesc si aici
(de obicei fol pipreqs dar nu parea sa mearga bine cu notebooks in venv)
pip freeze > requirements.txt
libraries

```
asttokens==2.4.1
attrs==23.1.0
cattrs==23.2.3
certifi==2023.11.17
charset-normalizer==3.3.2
click==8.1.7
colorama==0.4.6
comm==0.2.0
contourpy==1.2.0
cycler==0.12.1
debugpy==1.8.0
decorator==5.1.1
docopt==0.6.2
executing==2.0.1
fonttools==4.46.0
idna==3.6
ipykernel==6.27.1
ipython==8.18.1
jedi==0.19.1
jupyter_client==8.6.0
jupyter_core==5.5.0
kiwisolver==1.4.5
lsprotocol==2023.0.0
markdown-it-py==3.0.0
matplotlib==3.8.2
matplotlib-inline==0.1.6
mdurl==0.1.2
nest-asyncio==1.5.8
numpy==1.26.2
opencv-python==4.8.1.78
packaging==23.2
parso==0.8.3
Pillow==10.1.0
platformdirs==4.0.0
prompt-toolkit==3.0.41
psutil==5.9.6
pure-eval==0.2.2
pygls==1.2.1
Pygments==2.17.2
pyparsing==3.1.1
python-dateutil==2.8.2
pywin32==306
pyzmq==25.1.1
requests==2.31.0
rich==13.7.0
ruff==0.1.6
ruff-lsp==0.0.45
shellingham==1.5.4
six==1.16.0
stack-data==0.6.3
tornado==6.4
traitlets==5.14.0
typer==0.9.0
typing_extensions==4.8.0
urllib3==2.1.0
wcwidth==0.2.12
yarg==0.1.9
```