# 🧠 M2 - MemoryCost (Page Fault and Memory Analysis)

Projeto desenvolvido para o trabalho **M2** da disciplina **Sistemas Operacionais – UNIVALI**.

O objetivo é medir e analisar o comportamento de **paginação**, **page faults** e **uso de memória** em diferentes cenários, incluindo:
- Alocação intensiva de memória (`MemoryCost`)
- Execução multithread (`ThreadsStress`)
- Ordenação de grandes vetores (`SortingStress`)


## 📁 Estrutura do Projeto

M2-MemoryCost/
│
├── MemoryCost/ # Programa principal de análise de alocação de memória
│ ├── memory_cost_mod.cpp
│ └── CMakeLists.txt
│
├── ThreadsStress/ # Teste de uso de memória com múltiplas threads
│ ├── threads_stress_mod.cpp
│ └── CMakeLists.txt
│
├── SortingStress/ # Teste de algoritmos de ordenação
│ ├── algOrdenacao.cpp / algOrdenacao.hpp
│ ├── ordenacao_stress.cpp
│ └── CMakeLists.txt
│
├── scripts/ # Scripts de execução e coleta
│ ├── run_linux.sh / run_windows.ps1 # Executam todos os módulos
│ ├── collect_linux.sh / collect_windows.ps1
│
├── results/ # Resultados gerados automaticamente
│ └── *.csv
│
├── CMakeLists.txt
└── README.md

---

## ⚙️ Compilação

### 🔹 Linux

``bash
# Clonar repositório
git clone https://github.com/Gabyz04/M2-MemoryCost.git
cd M2-MemoryCost

# Dar permissão de execução aos scripts (apenas na primeira vez)
chmod +x scripts/*.sh

# Executar testes
./scripts/run_linux.sh 4 1000000 1 seq 16 20

🔸 Parâmetros (nessa ordem):

threads → número de threads

blocksize → tamanho do bloco de memória (em inteiros)

allocs → número de alocações

pattern → padrão de acesso (seq ou rand)

stride → espaçamento de acesso à memória

duration → tempo de execução em segundos

🔸 O script executa automaticamente:

MemoryCost (teste de page faults e alocação)

ThreadsStress (teste de uso intensivo de threads)

SortingStress (teste de ordenação de grandes vetores)

Os resultados são salvos na pasta results/.

### 🔹 Windows

# Clonar repositório
git clone https://github.com/Gabyz04/M2-MemoryCost.git
cd M2-MemoryCost

# Executar testes
.\scripts\run_windows.ps1 -threads 4 -blocksize 1000000 -allocs 1 -pattern seq -stride 16 -duration 20

O script realiza o build automático via CMake, executa os três módulos e grava os resultados em results\.

## 🧪 Coleta de Dados

Os scripts de coleta permitem medir page faults e uso de memória durante a execução.

### 🔹 Linux

bash scripts/collect_linux.sh

# Exemplo de comando manual:
ps -o pid,comm,min_flt,maj_flt,rss,vsz $(pidof memory_cost_mod)

### 🔹 Windows

# Executa coleta via Process Explorer ou script PowerShell
.\scripts\collect_windows.ps1

## 📊 Visualização dos Resultados

Após os testes, é possível gerar gráficos e análises com:

python3 scripts/visualizar_memorycost.py

O gráfico será salvo em results/memorycost_graph.png.

## 📦 Saídas Geradas

results/memory_results.csv → Dados brutos coletados.

results/memorycost_graph.png → Gráfico de consumo de memória.

## 🧰 Dependências

Linux: g++, cmake, bash, python3

Windows: PowerShell, Visual Studio Build Tools, Python

Python libs: matplotlib, pandas (para visualização dos resultados)

## 🏁 Observações

Antes de executar novos testes, limpe o cache de memória no Linux:

sudo sh -c "echo 3 > /proc/sys/vm/drop_caches"


    - Execute os testes em diferentes cenários (com e sem múltiplas aplicações abertas).

    - Para o relatório, registre capturas de tela do monitor de desempenho (Process Explorer, htop, etc.).

## 📚 Créditos

Baseado no código disponibilizado pelo professor Felipe Viel no repositório oficial de referência:
https://github.com/VielF/SO-Codes/tree/main/Memory/MemoryCost