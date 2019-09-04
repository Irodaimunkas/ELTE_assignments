<?php

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

//deleted the credentials here, for safety reasons of course
function dbKapcsolodas()
{
  $dbConnectionString = 'mysql:host=localhost;dbname=';
  $dbUserName = '';
  $dbPassword = '';
  return kapcsolodas($dbConnectionString, $dbUserName, $dbPassword);
}

$kapcsolat = dbKapcsolodas();
