#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tabpersonnel->setModel(tmppersonnel.afficher());
     ui->tabservice->setModel(tmpservice.afficher());
    ui->cin_per->setValidator(new QIntValidator(0,9999,this));
     ui->cin_chef->setValidator(new QIntValidator(0,9999,this));
      ui->id_service->setValidator(new QIntValidator(0,9999,this));
      ui->id_service_sup->setValidator(new QIntValidator(0,9999,this));
     ui->type_service->setMaxLength(9);
     ui->nom_per->setMaxLength(9);
     ui->prenom_per->setMaxLength(9);
     ui->type_per->setMaxLength(9);



}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_vehicule_clicked()
{
    int cin = ui->cin_per->text().toInt();
   QString type= ui->type_per->text();
     QString nom= ui->nom_per->text();
       QString prenom= ui->prenom_per->text();
  personnel p(cin,nom,prenom ,type);
  bool test=p.ajouter();
  if(test)
{ui->tabpersonnel->setModel(tmppersonnel.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un personnel"),
                  QObject::tr("personnel ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un personnel"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_supprimer_vehicule_clicked()
{
    int cin = ui->cin_pers->text().toInt();
        bool test=tmppersonnel.supprimer(cin);
        if(test)
        {ui->tabpersonnel->setModel(tmppersonnel.afficher());//refresh


            QMessageBox::information(nullptr, QObject::tr("Supprimer un personnel"),
                        QObject::tr("personnel supprimé.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un personnel"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
             }





void MainWindow::on_ajouter_vehicule_2_clicked()
{
    int idservice = ui->id_service->text().toInt();
    int cinchef= ui->cin_chef->text().toInt();
     QString typeservice= ui->type_service->text();

  service s (idservice,cinchef ,typeservice);
  bool test=s.ajouter();
  if(test)
{ui->tabservice->setModel(tmpservice.afficher());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter un service"),
                  QObject::tr("service ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un service"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_supprimer_panne_clicked()
{
    long idservice=ui->id_service_sup->text().toLong();
    bool test=tmpservice.supprimer(idservice);
    if(test)
    {ui->tabservice->setModel(tmpservice.afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un service"),
                    QObject::tr(" service supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un service"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


//modifierperso
void MainWindow::on_modifier_vehicule_clicked()
{


            if (ui->modifier_vehicule->isChecked())
            {

                ui->modifier_vehicule->setText("Modifiable");
                QSqlTableModel *tableModel= new QSqlTableModel();
                tableModel->setTable("PERSONNEL");
                tableModel->select();
                ui->tabpersonnel->setModel(tableModel);
            }
            else
            {
                ui->modifier_vehicule->setText("Modifier");
                ui->tabpersonnel->setModel(tmppersonnel.afficher());


            }




}
//modifierservice
void MainWindow::on_modifier_service_clicked()
{
    if (ui->modifier_service->isChecked())
    {

        ui->modifier_service->setText("Modifiable");
        QSqlTableModel *tableModel= new QSqlTableModel();
        tableModel->setTable("SERVICE");
        tableModel->select();
        ui->tabservice->setModel(tableModel);
    }
    else
    {
        ui->modifier_service->setText("Modifier");
        ui->tabservice->setModel(tmpservice.afficher());


    }

}
// rechercher

void MainWindow::on_rb_clicked()
{
    QString rech =ui->rechline->text();
        ui->tabpersonnel->setModel(tmppersonnel.rechercher(rech));
}

void MainWindow::on_tri_clicked()
{
    personnel *r = new personnel();
    ui->tabpersonnel->setModel(r->tri());
}
//service
void MainWindow::on_rb_2_clicked()
{
    QString rech =ui->rechline_2->text();
        ui->tabservice->setModel(tmpservice.rechercher(rech));
}

void MainWindow::on_tri_2_clicked()
{
    service *r = new service();
    ui->tabservice->setModel(r->tri());

}

void MainWindow::on_pdf_clicked()
{
            QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tabpersonnel->model()->rowCount();
                    const int columnCount =ui->tabpersonnel->model()->columnCount();

                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("PERSONNEL")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<img src='D:/qt/wedd/5739.PNG' width='100' height='100'>\n"
                                "<h1>Liste des personnels</h1>"



                                "<table border=1 cellspacing=0 cellpadding=2>\n";


                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tabpersonnel->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tabpersonnel->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tabpersonnel->isColumnHidden(column)) {
                                       QString data = ui->tabpersonnel->model()->data(ui->tabpersonnel->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";

                           QTextDocument *document = new QTextDocument();
                           document->setHtml(strStream);

                           QPrinter printer;

                           QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                           if (dialog->exec() == QDialog::Accepted) {
                               document->print(&printer);
                        }
}
