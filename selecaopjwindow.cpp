#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include <vector>
#include <algorithm>

#include <QTextDocument>

#include "selecaopjwindow.h"
#include "ui_selecaopjwindow.h"

SelecaoPJWindow::SelecaoPJWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelecaoPJWindow)
{
    ui->setupUi(this);
}

void SelecaoPJWindow::selecionarArquivo(int numeroArquivo){
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Carregar arquivo texto"),
                                                    "/home/",
                                                    tr("Arquivo de texto (*.txt);; Todos os arquivos (*)"));

    switch (numeroArquivo) {
        case 1:
            this->diretorioArquivoUm = filename.toUtf8().constData();
            ui->lineEditArq_1->setText(this->diretorioArquivoUm.c_str());
        break;
        case 2:
            this->diretorioArquivoDois = filename.toUtf8().constData();
            ui->lineEditArq_2->setText(this->diretorioArquivoDois.c_str());
        break;
        default:
        break;
    }
}

std::string fileToString(std::string diretorioGenerico){

    std::string conteudoGenerico = "";

    try {
        std::ifstream file(diretorioGenerico);
        if (!file) {
        }else {
            while(!file.eof()){
                std::string line;
                file >> line;
                conteudoGenerico += line;
            }
        }
    }
    catch(int e){
        std::cerr << e << std::endl;
    }

    return conteudoGenerico;
}

void SelecaoPJWindow::carregarArquivo(int numeroArquivo){

    std::string conteudoGenerico = "";
    std::string diretorioGenerico = "";

    switch (numeroArquivo) {
        case 1:
            diretorioGenerico = this->diretorioArquivoUm;
        break;
        case 2:
            diretorioGenerico = this->diretorioArquivoDois;
        break;
    }

    switch (numeroArquivo) {
        case 1:
            this->conteudoArquivoUm = conteudoGenerico;
            this->diretorioArquivoUm = diretorioGenerico;
            ui->plainTextEditConteudo->setPlainText(fileToString(this->diretorioArquivoUm).c_str());
        break;
        case 2:
            this->conteudoArquivoDois = conteudoGenerico;
            this->diretorioArquivoDois = diretorioGenerico;
            ui->plainTextEditConteudo->setPlainText(fileToString(this->diretorioArquivoDois).c_str());
        break;
        default:
            std::string ambos = fileToString(this->diretorioArquivoUm) + fileToString(this->diretorioArquivoDois);
            ui->plainTextEditConteudo->setPlainText(ambos.c_str());
        break;
    }
}

bool sortDesc(const std::pair<int,int> &a,  const std::pair<int,int> &b)
{
    return (a.second > b.second);
}

/**
 * @brief ordenacao
 * @param conteudo
 * @param tipoOrdenacao Lexicografica = 1, Por ocorrência = 2
 * @return
 */
std::string ordenacao(std::string conteudo, int tipoOrdenacao){
    std::string conteudoOrdenado = "";
    std::map<char,int> mapCaracteres;

    for (char &caractere: conteudo) {
        mapCaracteres[std::toupper(caractere)]++;
    }

    switch (tipoOrdenacao) {
        case 1:
        for (auto &item: mapCaracteres) {
            std::stringstream stringstream;
            stringstream << item.first << " : " << item.second << "\n";
            conteudoOrdenado += stringstream.str();
        }
        break;
    case 2:
        std::vector<std::pair<char, int>> mapVector;
        // Insert entries
        for (auto iterator = mapCaracteres.begin(); iterator != mapCaracteres.end(); ++iterator){
            mapVector.push_back(*iterator);
        }

        sort(mapVector.begin(), mapVector.end(), sortDesc);

        for (int i = 0; i <mapVector.size(); i++) {
            std::stringstream stringstream;
            stringstream << mapVector[i].first << " -> " << mapVector[i].second << "\n";
            conteudoOrdenado += stringstream.str();
        }
        break;
    }

    return conteudoOrdenado;
}

SelecaoPJWindow::~SelecaoPJWindow()
{
    delete ui;
}

void SelecaoPJWindow::on_pushButtonSelecionar_1_clicked(){ selecionarArquivo(1); }
void SelecaoPJWindow::on_pushButtonSelecionar_2_clicked(){ selecionarArquivo(2); }
void SelecaoPJWindow::on_radioButtonExbArq_1_clicked(){ carregarArquivo(1); }
void SelecaoPJWindow::on_radioButtonExbArq_2_clicked(){ carregarArquivo(2); }
void SelecaoPJWindow::on_radioButtonExbArqAmbos_clicked(){ carregarArquivo(0); }

void SelecaoPJWindow::on_pushButtonOrdLexic_clicked()
{
    std::string plaintTextConteudo = fileToString(this->diretorioArquivoUm) +
                                     fileToString(this->diretorioArquivoDois);

    ui->plainTextEditConteudo->setPlainText(ordenacao(plaintTextConteudo.c_str(), 1).c_str());
}

void SelecaoPJWindow::on_pushButtonOrdOcorr_clicked()
{
    std::string plaintTextConteudo = fileToString(this->diretorioArquivoUm) +
                                     fileToString(this->diretorioArquivoDois);

    ui->plainTextEditConteudo->setPlainText(ordenacao(plaintTextConteudo.c_str(), 2).c_str());
}
