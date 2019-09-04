<?php

function is_empty($input, $key) {
  return !(isset($input[$key]) && $input[$key] !== '');
}

function validate($input, $rules, &$data, &$errors) {
  $errors = [];
  
  $filtered_inputs = filter_var_array($input, $rules);
  
  foreach ($filtered_inputs as $key => $value) {
    $data[$key] = null;
    if (is_null($value) || is_empty($input, $key)) {
      if (isset($rules[$key]['default'])) {
        $data[$key] = $rules[$key]['default'];
      } else {
        $errors[] = "{$key} hiányzik!";
      }
    }
    else if ($value === false) {
      $errors[] = $rules[$key]['errormsg'];
    }
    else {
      $data[$key] = $value;
    }
  }
  
  return !(bool)$errors;
}
