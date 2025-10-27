# M2 - MemoryCost (Page Fault and Memory Analysis)

Projeto desenvolvido para o trabalho M2 da disciplina **Sistemas Operacionais** (UNIVALI).

O objetivo é medir e analisar o comportamento de **paginação e page faults** em diferentes cenários de uso de memória,
incluindo múltiplas threads e diferentes padrões de alocação.

---

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
├── SortingStress/ # Teste de uso de memória com algoritmos de ordenação
│ ├── algOrdenacao.cpp / algOrdenacao.hpp
│ ├── ordenacao_stress.cpp
│ └── CMakeLists.txt
│
├── scripts/ # Scripts auxiliares
│ ├── run_linux.sh / run_windows.ps1 # Executar testes
│ ├── collect_linux.sh / collect_windows.ps1 # Coletar métricas
│ ├── visualizar_memorycost.py / .ps1 # Visualizar resultados
│
├── results/ # Resultados coletados
│ ├── memory_results.csv
│ └── memorycost_graph.png
│
├── build/ # Pasta de build (gerada pelo CMake)
├── CMakeLists.txt
└── README.md


---

## ⚙️ Compilação

### 🔹 Linux

``bash
# Clonar repositório
git clone https://github.com/Gabyz04/M2-MemoryCost.git
cd M2-MemoryCost

# Criar pasta de build e compilar
cmake -S . -B build
cmake --build build -- -j

# Executar teste básico
./build/MemoryCost/memory_cost_mod --size 1000000 --allocs 2 --threads 4 --pattern seq --stride 16 --duration 30 --output results/memory_results.csv


### 🔹 Windows

# Clonar repositório
git clone https://github.com/Gabyz04/M2-MemoryCost.git
cd M2-MemoryCost

# Executar via PowerShell
.\scripts\run_windows.ps1 -threads 4 -blocksize 1000000 -allocs 2 -pattern seq -stride 16 -duration 30

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