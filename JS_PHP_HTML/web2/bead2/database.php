<?php

/*
// http://webprogramozas.inf.elte.hu/phpmyadmin/

Adatbázis scriptek

create table kategoria (
  id integer primary key NOT NULL AUTO_INCREMENT,
  nev varchar(100) not null
) engine = InnoDB CHARSET=utf8 COLLATE utf8_hungarian_ci;

create table termek (
  id integer primary key NOT NULL AUTO_INCREMENT,
  nev varchar(100) not null,
  ar integer,
  kategoria_id integer not null,
  foreign key (kategoria_id) references kategoria(id) on update restrict on delete restrict
) engine = InnoDB CHARSET=utf8 COLLATE utf8_hungarian_ci;

insert into kategoria (nev) values ('Tejtermékek');
insert into termek (nev, ar, kategoria_id) values ('tej', 200, (select max(id) from kategoria));
insert into termek (nev, ar, kategoria_id) values ('túrórudi', 100, (select max(id) from kategoria));
insert into kategoria (nev) values ('Elektronikai eszközök');
insert into termek (nev, ar, kategoria_id) values ('pendrive 2GB', 4000, (select max(id) from kategoria));
insert into kategoria (nev) values ('Ruhák');
insert into kategoria (nev) values ('DVD filmek');
insert into termek (nev, ar, kategoria_id) values ('Shaun of the Dead', 1400, (select max(id) from kategoria));
insert into termek (nev, ar, kategoria_id) values ('Tucker and Dale vs Evil', 2000, (select max(id) from kategoria));
insert into kategoria (nev) values ('Rabszolgák');
insert into termek (nev, ar, kategoria_id) values ('Isaura', 365000, (select max(id) from kategoria));

-- drop table termek;
-+ drop table kategoria;

*/

function kapcsolodas($kapcsolati_szoveg, $felhasznalonev = '', $jelszo = '')
{
  $pdo = new PDO($kapcsolati_szoveg, $felhasznalonev, $jelszo);
  $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  $pdo->exec('set names UTF8');
  return $pdo;
}

function lekerdezes($kapcsolat, $sql, $parameterek = [])
{
  $stmt = $kapcsolat->prepare($sql);
  $stmt->execute($parameterek);
  return $stmt->fetchAll();
}

function vegrehajtas($kapcsolat, $sql, $parameterek = [])
{
  return $kapcsolat
    ->prepare($sql)
    ->execute($parameterek);
}

function dbKapcsolodas()
{
  $dbConnectionString = 'mysql:host=localhost;dbname=';
  $dbUserName = '';
  $dbPassword = '';
  return kapcsolodas($dbConnectionString, $dbUserName, $dbPassword);
}

$kapcsolat = dbKapcsolodas();