<?php

function load_from_json($fileName, $base = array()) {
  $s = @file_get_contents($fileName);
  return ($s === false 
    ? $base 
    : json_decode($s, true));
}

function save_to_json($fileName, $data) {
  $s = json_encode($data, JSON_PRETTY_PRINT);
  return file_put_contents($fileName, $s, LOCK_EX);
}