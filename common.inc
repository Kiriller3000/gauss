<?php
class matrix { //--------------------------------------------------------------

    public function set($str,$i,$j) {

        $val = explode ("/",$str);
        //$value_0 = $val[0] === "" ? 1 : floatval($val[0]);
        $value_0 = floatval($val[0]);
        if ($value_0 == 0) {
            $this->numerator[$i][$j] = abs($value_0); 
        } else {
            $this->numerator[$i][$j] = $value_0;    
        }
    
        if ( (empty($val[1])) or ($value_0 == 0) or (floatval($val[1]) == 0) ) {
            $this->denominator[$i][$j] = 1;
            return;
        } else {
             $this->denominator[$i][$j] = floatval($val[1]);
        }
        fraction::simplification($this->numerator[$i][$j], $this->denominator[$i][$j]);
        $this->numerator[$i][$j] = fraction::getSimlNum();
        $this->denominator[$i][$j] = fraction::getSimplDen();
    } 
  
    public function get_num() {
      return $this->numerator;
    }
    public function get_den() {
      return $this->denominator;
    }
    private $numerator = array();
    private $denominator = array();
}

class fraction { //-------------------------------------------------------------
    //Group of simplification function
    public static function simplification($num, $den) {

        if ($num == 0) { $num = abs($num);$den = 1; }
            
        if ($den < 0) { $num *= -1;$den *= -1; }
        
        if ( abs($den) <= abs($num) ) $N = abs($den); else $N = abs($num);
        
        if ($N > 1000) $N = 1000; 
        
        for ($i = $N; $i >= 1; $i--) {
            if ( ($num % $i === 0) && ($den % $i === 0) ) {
                fraction::$simplNum = $num / $i;
                fraction::$simplDen = $den / $i;
                return;    
            }
        }   
        fraction::$simplNum = $num;
        fraction::$simplDen = $den;
    }
    public static function inversion($val) {       
        if ($val == 0) {
            $val = abs($val);
        } else {
            $val *= -1;    
        }
        return $val;
    }
    public static function getSimlNum() {
        return fraction::$simplNum;
    }
    public static function getSimplDen() {
        return fraction::$simplDen;
    }
    //End group of simplification function
     
     
    //Group of division function
    public static function division($num1, $den1, $num2, $den2) {
        $num = $num1 * $den2;
        $den = $den1 * $num2;
        if ($den < 0) {
            $num *= -1;
            $den *= -1;
        }
        //$this->simplification($num, $den);
        fraction::$numOfDiv = $num;//$this->getSimlNum();
        fraction::$denOfDiv = $den;//$this->getSimplDen(); 
    }
    public static function getNumOfDiv() {
        return fraction::$numOfDiv;
    }
    public static function getDenOfDiv() {
        return fraction::$denOfDiv;
    }
    //End group of division function
    
    
    //Group of sum function 
    public static function sum($num1, $den1, $num2, $den2) {
        $commonDen = $den1 * $den2;
        $num = $num1 * $den2 + $num2 * $den1;
        if ($num == 0) { 
            $commonDen = 1;
            fraction::$numOfSum = $num;
            fraction::$denOfSum = $commonDen;
            return; 
        }
        fraction::simplification($num, $commonDen);
        fraction::$numOfSum = fraction::getSimlNum();
        fraction::$denOfSum = fraction::getSimplDen(); 
    }
    public static function getNumOfSum() {
        return fraction::$numOfSum;
    }
    public static function getDenOfSum() {
        return fraction::$denOfSum;
    }
    //End group of sum function   
    
    //Group of minus function 
    public static function minus($num1, $den1, $num2, $den2) {
        $commonDen = $den1 * $den2;
        $num = $num1 * $den2 - $num2 * $den1;
        if ($num == 0) { 
            $commonDen = 1;
            fraction::$numOfMinus = $num;
            fraction::$denOfMinus = $commonDen;
            return; 
        }
        fraction::simplification($num, $commonDen);
        fraction::$numOfMinus = fraction::getSimlNum();
        fraction::$denOfMinus = fraction::getSimplDen(); 
    }
    public static function getNumOfMinus() {
        return fraction::$numOfMinus;
    }
    public static function getDenOfMinus() {
        return fraction::$denOfMinus;
    }
    //End group of minus function
    
    //Set function
        public static function setFrac($str) {

        $val = explode ("/",$str);
        //$value_0 = $val[0] === "" ? 1 : floatval($val[0]);
        $value_0 = floatval($val[0]);
        if ($value_0 == 0) {
            fraction::$numOfFrac = abs($value_0); 
        } else {
            fraction::$numOfFrac = $value_0;    
        }
    
        if ( (empty($val[1])) or ($value_0 == 0) or (floatval($val[1]) == 0) ) {
            fraction::$denOfFrac = 1;
            return;
        } else {
            fraction::$denOfFrac = floatval($val[1]);
        }
        fraction::simplification(fraction::$numOfFrac, fraction::$denOfFrac);
        fraction::$numOfFrac = fraction::getSimlNum();
        fraction::$denOfFrac = fraction::getSimplDen();
    } 
  
    public static function get_numOfFrac() {
      return fraction::$numOfFrac;
    }
    public static function get_denOfFrac() {
      return fraction::$denOfFrac;
    }
    //End of set function
    
    public static $numOfFrac, $denOfFrac;
    public static $simplNum, $simplDen;
    public static $numOfDiv, $denOfDiv;
    public static $numOfSum, $denOfSum;
    public static $numOfMinus, $denOfMinus;
    
} // End of class fraction -----------------------------------

//Print functions
function func_output( $matrix_num, $matrix_den, $i, $j) {
  
  if (  ( $j == 1 ) or ( $j == count($matrix_num[1]) )  ) {
  
      if (  ( $matrix_num[$i][$j] == 0 ) or ($matrix_den[$i][$j] == 1)  ) {    
          $out = "{$matrix_num[$i][$j]}";
          return $out;
      }
      elseif (  ( $matrix_den[$i][$j] < 0 ) and ( $matrix_num[$i][$j] < 0)  ) {
        $matrix_num[$i][$j] = abs($matrix_num[$i][$j]);
        $matrix_den[$i][$j] = abs($matrix_den[$i][$j]);
        $out = "{$matrix_num[$i][$j]}/{$matrix_den[$i][$j]}";
        return $out;
      }
      elseif (  ( $matrix_num[$i][$j] > 0 ) and ( $matrix_den[$i][$j] < 0 )  ) {
        $matrix_num[$i][$j] = $matrix_num[$i][$j] * (-1);
        $matrix_den[$i][$j] = abs($matrix_den[$i][$j]); 
        $out = "{$matrix_num[$i][$j]}/{$matrix_den[$i][$j]}";
        return $out;
      }
      else {
        $out = "{$matrix_num[$i][$j]}/{$matrix_den[$i][$j]}";
        return $out;
      }
  }
  elseif (  ( $j > 1 ) or ( $j < count($matrix_num[1]) )  ){
      
      if (  ( $matrix_num[$i][$j] == 0 ) or ($matrix_den[$i][$j] == 1)  ) {    
        $out = $matrix_num[$i][$j];
        if ( $out >= 0 ) $out = "+".$out;
        return $out;
      } 
      elseif (  ( $matrix_den[$i][$j] < 0 ) and ( $matrix_num[$i][$j] < 0)  ) { 
        $matrix_num[$i][$j] = abs($matrix_num[$i][$j]);
        $matrix_den[$i][$j] = abs($matrix_den[$i][$j]);
        $out = "{$matrix_num[$i][$j]}/{$matrix_den[$i][$j]}";
        $out = "+".$out;
        return $out;
      }
      elseif (  ( $matrix_num[$i][$j] > 0 ) and ( $matrix_den[$i][$j] < 0 )  ) {
        $matrix_num[$i][$j] = $matrix_num[$i][$j] * (-1);
        $matrix_den[$i][$j] = abs($matrix_den[$i][$j]); 
        $out = "{$matrix_num[$i][$j]}/{$matrix_den[$i][$j]}";
        return $out;
      }
      elseif (  ( $matrix_num[$i][$j] > 0 ) and ( $matrix_den[$i][$j] > 0 )  ) {
        $out = "{$matrix_num[$i][$j]}/{$matrix_den[$i][$j]}";
        $out = "+".$out;
        return $out;
      }
      else {
        $out = "{$matrix_num[$i][$j]}/{$matrix_den[$i][$j]}";
        return $out;
      }
  }
}

function printM($matrix, $matrix_num = 0, $matrix_den = 0, $tick = 0) {
 
    if ($matrix !== 0) {
        $matrix_num = $matrix->get_num();
        $matrix_den = $matrix->get_den();
    }
    
  $countNum_I = count($matrix_num);
  $countNum_J = count($matrix_num[1]);
  echo "<table>\n";
      for ($i=1; $i <= $countNum_I; $i++) {
        echo "<tr>\n";
        $flag = FALSE;        
        for ($j=1; $j < $countNum_J; $j++) {
          
              if (func_output($matrix_num, $matrix_den, $i, $j) == 0) {
                $str = func_output( $matrix_num, $matrix_den, $i, $j);
                echo "<td nowrap align='right'><font color='#ACACAC'>&nbsp;&nbsp;&nbsp;&nbsp;{$str}&nbsp;<b>x<sub>$j</sub></b></font></td>\n";
              } else {
                  $flag = TRUE;
                  if ( !(($tick <= $j) && ($tick > 0)) ) {               
                        echo "<td nowrap align='right'>&nbsp;&nbsp;&nbsp;&nbsp;",func_output( $matrix_num, $matrix_den, $i, $j),"&nbsp;<b>x<sub>$j</sub></b></td>\n";
                  } else echo "<td align='right'>&nbsp;&nbsp;&nbsp;&nbsp;",func_output( $matrix_num, $matrix_den, $i, $j),"&nbsp;</td>\n";
                }
              
              
        }
        if ( (func_output($matrix_num, $matrix_den, $i, $j) == 0) && (!$flag) ) {
            $str = func_output( $matrix_num, $matrix_den, $i, $j);
            echo "<td><font color='#ACACAC'>&nbsp;&nbsp;&nbsp;&nbsp;=</font></td><td align='right'><font color='#ACACAC'>&nbsp;&nbsp;&nbsp;&nbsp;{$str}</font></td>";
        } else {
            echo "<td>&nbsp;&nbsp;&nbsp;&nbsp;=</td><td align='right'>&nbsp;&nbsp;&nbsp;&nbsp;".func_output( $matrix_num, $matrix_den, $i, $j)."</td>\n";
        }
        echo "</tr>\n";
      } 
  echo "</table>\n";

}
//End of print functions
?>

