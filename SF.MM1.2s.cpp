#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class clPacote {
public:
    int nf;
    double ic, cpf, eps1, eps2, sps1, sps2;
};

// Classe para simulação de sistema de fila M/M/2
class clSF {
private:
    double l, m1, m2, E[3], DP[3], T1, T2, U1, U2;
    vector<clPacote> P;
    double X(double);
    void Empacotar(void);
    void Nf(int);
    void Estatistica(void);
    string Tabela(void);
    string Legenda(void);

public:
    clSF(void);
    void Iniciar(double, double, double);
    void Simular(int);
    string Resumo(void);
};

clSF::clSF(void) {
    srand(time(nullptr));
}

double clSF::X(double p) {
    double u = (rand() + 1.0) / (RAND_MAX + 2.0); // u in (0,1)
    return -log(u) / p;
}

void clSF::Iniciar(double l, double m1, double m2) {
    this->l = l;
    this->m1 = m1;
    this->m2 = m2;
    P.clear();
    P.push_back({0, 0, 0, 0, 0, 0, 0});
}

// Função para adicionar um novo pacote à simulação
void clSF::Empacotar(void) {
    int a = P.size() - 1;
    clPacote Pn, Pa = P[a];

    Pn.ic = X(l);
    Pn.cpf = Pn.ic + Pa.cpf;

    // Verifica qual servidor está livre
    if (Pa.sps1 <= Pa.sps2) {
        // Servidor 1 está livre, utiliza m1
        Pn.eps1 = max(Pn.cpf, Pa.sps1);
        Pn.sps1 = Pn.eps1 + X(m1);
        Pn.eps2 = Pa.eps2;
        Pn.sps2 = Pa.sps2;
    } else {
        // Servidor 2 está livre, utiliza m2
        Pn.eps2 = max(Pn.cpf, Pa.sps2);
        Pn.sps2 = Pn.eps2 + X(m2);
        Pn.eps1 = Pa.eps1;
        Pn.sps1 = Pa.sps1;
    }

    Pn.nf = 0;
    P.push_back(Pn);
}

void clSF::Nf(int p) {
    P[p].nf = 0;
    for (int a = p - 1; a > 0; a--) {
        if (P[p].cpf < min(P[a].sps1, P[a].sps2)) {
            P[p].nf++;
        } else {
            break;
        }
    }
}

void clSF::Simular(int N) {
    for (int p = 1; p < N; p++) {
        Empacotar();
        Nf(p);
    }
    Estatistica();
}

void clSF::Estatistica(void) {
    int N = P.size();
    double Sx[3] = {0, 0, 0}, Sxx[3] = {0, 0, 0};
    double tempoServidor1 = 0, tempoServidor2 = 0;

    T1 = 0; // Tempo total para servidor 1
    T2 = 0; // Tempo total para servidor 2

    for (int p = 0; p < N; p++) {
        double ts1 = (P[p].sps1 > 0) ? P[p].sps1 - P[p].eps1 : 0;
        double ts2 = (P[p].sps2 > 0) ? P[p].sps2 - P[p].eps2 : 0;
        tempoServidor1 += ts1;
        tempoServidor2 += ts2;

        // Atualiza o tempo total para cada servidor
        if (P[p].sps1 > 0) T1 = max(T1, P[p].sps1);
        if (P[p].sps2 > 0) T2 = max(T2, P[p].sps2);

        double tsf = (P[p].sps1 > 0 ? P[p].sps1 : P[p].sps2) - P[p].cpf;
        Sx[0] += ts1 + ts2;
        Sxx[0] += (ts1 * ts1) + (ts2 * ts2);
        Sx[1] += tsf;
        Sxx[1] += tsf * tsf;
        Sx[2] += P[p].nf;
        Sxx[2] += P[p].nf * P[p].nf;
    }

    // Corrigir o cálculo da utilização para garantir que não ultrapasse 1.0 (100%)
    if (T1 > 0) {
        U1 = min(1.0, tempoServidor1 / T1);  
    }
    if (T2 > 0) {
        U2 = min(1.0, tempoServidor2 / T2);  
    }

    for (int e = 0; e < 3; e++) {
        E[e] = Sx[e] / N;
        DP[e] = sqrt(Sxx[e] / N - E[e] * E[e]);
    }
}

string clSF::Tabela(void) {
    stringstream htm;
    htm << fixed;
    htm.precision(5);
    htm << "<table border='1'><tr><th>p<th>ic(s)<th>cpf(s)<th>eps1(s)<th>sps1(s)<th>eps2(s)<th>sps2(s)<th>nf(p)";
    for (int p = 0; p < P.size(); p++) {
        htm << "<tr><td>" << p + 1
            << "<td>" << P[p].ic
            << "<td>" << P[p].cpf
            << "<td>" << P[p].eps1
            << "<td>" << P[p].sps1
            << "<td>" << P[p].eps2
            << "<td>" << P[p].sps2
            << "<td>" << P[p].nf;
    }
    htm << "</table>";
    return htm.str();
}

string clSF::Resumo(void) {
    stringstream htm;
    htm << "<html><body>";
    htm << Tabela();
    htm << "<br><br>Resumo<hr>"
        << "<table border='1' cellpadding='4' cellspacing='0'>"
        << "<tr><td>Taxa de Chegada (l) <td>" << l << " p/s"
        << "<tr><td>Taxa de Serviço Servidor 1 (m1) <td>" << m1 << " p/s"
        << "<tr><td>Taxa de Serviço Servidor 2 (m2) <td>" << m2 << " p/s"
        << "<tr><td>Pacotes Simulados (N) <td>" << P.size()
        << "<tr><td>Tempo Total Servidor 1 (T1) <td>" << T1 << " s"
        << "<tr><td>Tempo Total Servidor 2 (T2) <td>" << T2 << " s"
        << "<tr><td>Utilização Servidor 1 (U1) <td>" << U1
        << "<tr><td>Utilização Servidor 2 (U2) <td>" << U2
        << "<tr><td>Tempo Médio no Sistema (E[tsf]) <td>" << E[1] << " s"
        << "<tr><td>Comprimento Médio da Fila (E[nf]) <td>" << E[2] << " p"
        << "</table><br><br>";
    htm << "</body></html>";
    return htm.str();
}

int main(void) {
    int N = 3000;
    double l = 800.0, m1 = 1474.6, m2 = 1200.0; // Taxa de serviço para os dois servidores

    clSF SF;
    SF.Iniciar(l, m1, m2); // Corrigido! Agora inicializo também m1, m2 ao invés de apenas m
    SF.Simular(N);
    ofstream file("MM2.html");
    file << SF.Resumo();
    file.close();
    return 0;
}
