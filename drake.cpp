#include "drake.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QSqlQueryModel>
#include<QSqlQuery>
drake::drake()
{
    ID=0;
    nom=prenom=typechant="";

}

drake::drake(int ID,QString nom ,QString prenom ,QString typechant )
{
    this->ID=ID; this->nom=nom; this->prenom=prenom; this->typechant=typechant;


 }
   int drake:: getID(){return ID;}
    QString drake:: getnom(){return nom;}
     QString drake:: getprenom(){return prenom;}
     QString drake:: gettypechant(){return typechant;}
     void drake:: setID(int ID ){this->ID=ID;}
     void drake:: setnom(QString nom){this->nom=nom;}
     void drake:: setprenom(QString prenom){this->prenom=prenom;}
     void drake:: settypechant(QString typechant){this->typechant=typechant;}

bool drake:: ajouter()
{
     QSqlQuery query;
     QString id_string= QString::number(ID);

            query.prepare("INSERT INTO chant (id, nom, prenom,type_de_chant) "
                          "VALUES (:id, :forename, :surname, :typechant)");
            query.bindValue(":id",id_string);
            query.bindValue(":forename", nom);
            query.bindValue(":surname", prenom);
            query.bindValue(":typechant", typechant);
           return query.exec();}

bool drake::supprimer(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare(" Delete from chant where id=:id");
    query.bindValue(":id", res);

        return query.exec();}
QSqlQueryModel* drake::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT* FROM chant");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identenfiant"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("type_de_chant"));


  return  model;
}
bool drake::modifier()
{

        QSqlQuery query;
        QString id_string=QString::number(ID);

       query.prepare(" UPDATE chant SET ID=:ID,nom=:nom_chanteur,prenom=:prenom_chanteur,type_de_chant=:typchant WHERE ID=:ID");
              query.bindValue(":ID", id_string);
              query.bindValue(":nom_chanteur",nom);
                 query.bindValue(":prenom_chanteur",prenom);
              query.bindValue(":typchant",typechant);

              return query.exec();


}
