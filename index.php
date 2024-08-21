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

echo "<h2>Решение систем линейных уравнений методом Гаусса</h2><hr>";
?> 

<form action='handler.php' method=GET>
  <table>
    <tr>
      <td>Число неизвестных:</td>
      <td>
    <select name="variable">
      <option value=2>2</option>
      <option value=3>3</option>
      <option value=4>4</option>
      <option value=5>5</option>
      <option value=6>6</option>
    </select>
      </td>
    </tr>
        <tr>
      <td>Число уравнений:</td>
      <td>
    <select name="eqation">
      <option value=2>2</option>
      <option value=3>3</option>
      <option value=4>4</option>
      <option value=5>5</option>
      <option value=6>6</option>
    </select>
      </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td><input type="submit" value="Ввод"></td>
    </tr>
    
  </table>
</form>

</body>
</html>
