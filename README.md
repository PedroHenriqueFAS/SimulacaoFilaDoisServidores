
# Simulador de Sistema de Filas M/M/2

Este projeto implementa uma simulação de um sistema de filas M/M/2 em C++. O sistema possui dois servidores e processa pacotes com base em taxas de chegada e serviço definidas pelo usuário.

## 📌 Funcionalidades
- Simula um sistema de filas M/M/2 utilizando distribuição exponencial.
- Calcula estatísticas de desempenho como tempo médio de espera, utilização dos servidores e comprimento médio da fila.
- Gera um arquivo `MM2.html` com um resumo dos resultados da simulação em formato de tabela.

## 🛠️ Tecnologias Utilizadas
- **Linguagem:** C++
- **Bibliotecas:** `<cmath>`, `<ctime>`, `<vector>`, `<fstream>`, `<sstream>`, `<algorithm>`

## 📂 Estrutura do Código

- `clPacote`: Classe que representa um pacote no sistema, armazenando tempos de chegada e processamento.
- `clSF`: Classe principal que gerencia a simulação.
  - `Iniciar()`: Inicializa a simulação com taxas de chegada e serviço.
  - `Empacotar()`: Adiciona pacotes à fila e distribui entre os servidores.
  - `Simular(N)`: Executa a simulação com `N` pacotes.
  - `Estatistica()`: Calcula métricas de desempenho.
  - `Resumo()`: Gera um resumo da simulação em HTML.

## 🚀 Como Compilar e Executar

### Compilar:
```bash
g++ -o mm2_simulation mm2_simulation.cpp
```

### Executar:
```bash
./mm2_simulation
```
Isso gerará um arquivo `MM2.html` contendo os resultados da simulação.

## 📊 Parâmetros de Simulação
No `main()`, você pode alterar os seguintes valores:
```cpp
int N = 3000; // Quantidade de pacotes simulados
double l = 800.0; // Taxa de chegada (pacotes por segundo)
double m1 = 1474.6; // Taxa de serviço do Servidor 1
double m2 = 1200.0; // Taxa de serviço do Servidor 2
```

## 📄 Saída Gerada
O arquivo `MM2.html` conterá um resumo com:
- Taxa de chegada e serviço
- Tempo total de processamento por servidor
- Utilização dos servidores
- Tempo médio de permanência no sistema
- Comprimento médio da fila

## 📜 Licença
Este projeto está sob a licença MIT. Sinta-se à vontade para modificar e utilizar conforme necessário.

## 📚 O Modelo M/M/2 - Explicação Detalhada

O **M/M/2** é um modelo clássico de **teoria das filas** utilizado para modelar sistemas de espera, como sistemas de atendimento de chamadas, servidores de sites, entre outros. O modelo é descrito da seguinte forma:

### **O que significa M/M/2?**
- **M** (para **Markoviano**): Refere-se ao fato de que as chegadas de pacotes (ou clientes) seguem uma **distribuição exponencial** (processo de Poisson). Isso implica que o tempo entre as chegadas de pacotes é aleatório, mas tem uma taxa constante.
- **M** (segunda letra): Também se refere à **distribuição exponencial** dos **tempos de serviço**, ou seja, o tempo que um servidor leva para processar um pacote segue uma distribuição exponencial.
- **2**: Significa que o sistema possui **dois servidores** para processar os pacotes.

### **Características do Sistema M/M/2**
- **Taxa de Chegada (λ)**: A taxa média de chegada de pacotes ao sistema.
- **Taxa de Serviço (μ)**: A taxa média de serviço de cada servidor.
- **Número de Servidores (2)**: O sistema tem dois servidores que podem processar pacotes simultaneamente.

### **Como Funciona o Sistema M/M/2**
- **Chegada de Pacotes**: Os pacotes chegam de acordo com uma distribuição exponencial. Quando um pacote chega, ele é processado por um servidor disponível.
- **Servidores**: Se um servidor estiver livre, o pacote é imediatamente atendido. Se ambos os servidores estiverem ocupados, o pacote ficará em espera até que um servidor seja liberado.
- **Processamento**: O tempo de serviço também segue uma distribuição exponencial. Cada servidor pode processar pacotes de forma independente.

### **Fórmulas Importantes**
1. **Utilização do Servidor (ρ)**:
   
    $$
    ho = \frac{\lambda}{2 \mu}
    $$
   Onde \( $\lambda $ \) é a taxa de chegada e \($ \mu $\) é a taxa de serviço de cada servidor.

2. **Número Médio de Pacotes na Fila (Lq)**:
   $$
   L_q = \frac{(\frac{\lambda}{\mu})^2}{2! \cdot (1 - \frac{\lambda}{2 \mu})}
   $$

3. **Tempo Médio de Espera na Fila (Wq)**:
   $$
   W_q = \frac{L_q}{\lambda}
   $$

4. **Número Médio de Pacotes no Sistema (L)**:
    $$
    L = L_q + \frac{\lambda}{\mu}
    $$


5. **Tempo Médio no Sistema (W)**:
    $$
    W = W_q + \frac{1}{\mu}
    $$


### **Exemplo de Aplicação**
Suponha que você tenha um sistema de atendimento de chamadas em um call center:
- \( $ \lambda = 10 $\) chamadas por minuto (taxa de chegada).
- \( $ \mu = 5 $ \) chamadas por minuto (taxa de serviço de cada atendente).
- O modelo M/M/2 pode ser usado para prever métricas como o número de chamadas na fila, o tempo de espera e a utilização dos atendentes.

---

Esse modelo é útil para otimizar sistemas de filas e pode ser aplicado em diversos cenários, como telemarketing, servidores web, hospitais, etc. Ele ajuda a entender a dinâmica do sistema e a prever problemas como sobrecarga e longos tempos de espera.
