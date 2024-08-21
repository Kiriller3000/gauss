<!DOCTYPE html>
<html>
 <head>
   <title>Решение систем линейных уравнений методом гаусса</title>
   <meta charset="utf-8">
 </head>
 <body>
<?php
ini_set('display_errors',1);
error_reporting(E_ALL);
include('sessset.inc');

if (isset($_GET['click'])) { goto label; }

if ( !isset($_GET['equat']) ) { header("Location: index.php");return; }

$_SESSION['equat'] = $_GET['equat'];
$_SESSION['var'] = $_GET['var'];


for ($i=1; $i <= $_SESSION['equat'] ;$i++) {
  for ($j=1; $j <= $_SESSION['var'] + 1; $j++) {
      $_SESSION["'$i$j'"] = $_GET["$i$j"]; 
  }
}  
 
label:

require_once ("common.inc");
require_once ("solution.inc");
                                                      
$matrix = new matrix();
$equa = $_SESSION['equat'];
$va = $_SESSION['var'];

$ExtVar = $va + 1;
for ($i=1; $i <= $equa; $i++) {
  for ($j=1; $j <= $ExtVar; $j++) {
    $matrix->set($_SESSION["'$i$j'"], $i, $j);
  }
}
 
echo "<p><b>Исходная система&nbsp;:</b></p>\n";
printM($matrix);

directMove($matrix);
?>
</body>
</html>