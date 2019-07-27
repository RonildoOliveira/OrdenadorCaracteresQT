#ifndef SELECAOPJWINDOW_H
#define SELECAOPJWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>

namespace Ui {
class SelecaoPJWindow;
}

class SelecaoPJWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelecaoPJWindow(QWidget *parent = nullptr);
    void selecionarArquivo(int numeroArquivo);
    void carregarArquivo(int numeroArquivo);
    ~SelecaoPJWindow();

private slots:
    void on_pushButtonSelecionar_1_clicked();
    void on_pushButtonSelecionar_2_clicked();

    void on_radioButtonExbArq_1_clicked();
    void on_radioButtonExbArq_2_clicked();
    void on_radioButtonExbArqAmbos_clicked();

    void on_pushButtonOrdLexic_clicked();

    void on_pushButtonOrdOcorr_clicked();

private:
    Ui::SelecaoPJWindow *ui;

    std::string diretorioArquivoUm;
    std::string diretorioArquivoDois;

    std::string conteudoArquivoUm;
    std::string conteudoArquivoDois;
};

#endif // SELECAOPJWINDOW_H
