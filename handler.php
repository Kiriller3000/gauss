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
 
if (!isset($_GET["eqation"])) { header("Location: index.php");return; };
$equat=(int)$_GET["eqation"];
$var=(int)$_GET["variable"];

echo "<p>Укажите коэффициенты и свободные члены</p><hr><br>\n";
echo "<form action='action.php' method='GET'>\n";
echo "<table>\n";
  for ($i=1; $i <= $equat; ++$i) {
    echo "<tr>\n";
    
    for ($j=1; $j <= $var; ++$j)
      echo "<td nowrap><input type='text' maxlength='6' size='6' name='$i$j'>X<sub>$j</sub></td>\n";
      
      echo "<td>&nbsp;&nbsp;=&nbsp;&nbsp;</td><td><input type='text' maxlength='6' size='6' name='$i$j'></td>\n";
    echo "</tr>\n";  
  }
  echo "<tr><td>&nbsp;</td></tr>\n"; 
  echo "<tr><td><input type=submit value='Решить'></td></tr>\n";
echo "</table>\n";
echo "<input type='hidden' name='equat' value=$equat>\n";
echo "<input type='hidden' name='var' value=$var>\n";
echo "</form>\n";

echo "<p><i><small><b>Примечание: дробные числа можно указывать через '/' (например: '1/2', '7/3' ). </b></small></i></p>";
?>
</body>
</html>
