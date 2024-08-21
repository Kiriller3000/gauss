<?php
function directMove($matrix) {
    $mNum = $matrix->get_num();
    $mDen = $matrix->get_den();
    define("COUNT_VAR", count($mNum[1]) - 1);
    define("COUNT_EQUAT", count($mNum));
    define("COUNT_I", min(COUNT_EQUAT, COUNT_VAR));
    $frac = new fraction();  
    echo "<p><b>Прямой ход Гаусса&nbsp;:</b></p>\n";
    $step = 0;
    $checkmark = FALSE;
    for ($i = 1; $i <= COUNT_I; $i++) {
        $flag = TRUE;
        if ($mNum[$i][$i] == 0) {
            $flag = FALSE;
            for ($k = $i + 1; $k <= COUNT_EQUAT; $k++) {
                if ($mNum[$k][$i] != 0) {
                    for ($j = $i; $j <= COUNT_VAR+1; $j++) {
                        $vector_num[$j] = $mNum[$i][$j];
                        $vector_den[$j] = $mDen[$i][$j];
                        $mNum[$i][$j] = $mNum[$k][$j];
                        $mDen[$i][$j] = $mDen[$k][$j];
                        $mNum[$k][$j] = $vector_num[$j];
                        $mDen[$k][$j] = $vector_den[$j];
                    }
                    $flag = TRUE;
                    echo "<br>Поменяли местами {$i}-е и {$k}-е уравнения&nbsp;\n";
                    printM(0, $mNum, $mDen); 
                    break;
                }
            }    
        }
        if ($flag === TRUE) {
            $checkmark = TRUE;
            for ($l = 1; $l <= (COUNT_EQUAT - $i); $l++) {
                if ($mNum[$i+$l][$i] != 0) {
                    ++$step;
                    $simp = 0;
                    $frac->division($mNum[$i+$l][$i], $mDen[$i+$l][$i], $mNum[$i][$i], $mDen[$i][$i]);
                    $fracNum = $frac->getNumOfDiv() * (-1);
                    $fracDen = $frac->getDenOfDiv();
                    
                    for ($j = $i; $j <= COUNT_VAR+1; $j++) {
                       $_num = $fracNum * $mNum[$i][$j];
                       $_den = $fracDen * $mDen[$i][$j];
                       $frac->sum($_num, $_den, $mNum[$i+$l][$j], $mDen[$i+$l][$j]);
                       $mNum[$i+$l][$j] = $frac->getNumOfSum();
                       $mDen[$i+$l][$j] = $frac->getDenOfSum();
                       if ($simp < $mDen[$i+$l][$j]) { $simp = $mDen[$i+$l][$j]; };
                    }
                    if ($simp != 1) {
                        for ($j = $i; $j <= COUNT_VAR+1; $j++) {    
                            $mNum[$i+$l][$j] = $mNum[$i+$l][$j] * $simp / $mDen[$i+$l][$j];
                            $mDen[$i+$l][$j] = 1;
                        }
                    }

                    $m = $i+$l;   
                    echo "<br>Шаг № {$step}:&nbsp;&nbsp;&nbsp;&nbsp;";
                    echo $i+$l."-е уравнение сложили с {$i}-ым помноженным на {$fracNum}",$fracDen == 1 ? "" : "/{$fracDen}", $simp == 1 ? "<br>" : "&nbsp;<b>;</b>&nbsp;&nbsp;&nbsp;{$m}-е разделили на 1/{$simp}<br>\n";
                    printM(0, $mNum, $mDen);
                }
            }
        } 
    }
    //putInOrder($mNum, $mDen);
    
    if ($checkmark === TRUE) {
        determine($mNum, $mDen);
    } else {
        $str = "<font color ='#000055'><b>Вы не ввели значений</b></font>\n";
        echo $str;
        return;
    }
}
function determine($mNum, $mDen) {

    for ($i = 1; $i <= COUNT_EQUAT; $i++) { $X[$i] = 0; };
    
    for ($i = 1; $i <= COUNT_EQUAT; $i++) {
        for ($j=1; $j <= COUNT_VAR; $j++) {
            if ($mNum[$i][$j] != 0) {
                $X[$i]++;
            }           
        }
    }
    //Если нет решений
    for ($i = COUNT_EQUAT; $i >= 1; $i--) {
        if ( ($mNum[$i][COUNT_VAR+1] != 0) && ($X[$i] == 0) ) {  
            $string = "";
            for ($j = 1; $j < COUNT_VAR; $j++) { 
                $string .= "0&nbsp; <b>x<sub>".$j."</sub></b>&nbsp; + &nbsp;";   
            }
            $string .= "0&nbsp; <b>x<sub>".$j."</sub></b>&nbsp; = &nbsp;\n";
            $string .= $mNum[$i][COUNT_VAR+1];
            $str = "<font color='#000055'><b>Система не имеет решений: {$string} :&nbsp;&nbsp;&nbsp; ранг матрицы системы меньше ранга расширенной матрицы системы:&nbsp;&nbsp;&nbsp; rang(A) < rang(A|B)</b></font>\n";
            echo $str;
            return;
        }
    }
    
    //Подсчет числа ненулевых строк
    $count_row = 0;
    for ($i = 1; $i <= COUNT_EQUAT; $i++) {
        if ( $X[$i] !=0 )  $count_row++; 
    } define('COUNT_ROW', $count_row);
    
    //Нахождение базисных переменных и свободных переменных
    if (COUNT_ROW < COUNT_VAR) {
        for ($i = 1; $i <= COUNT_I; $i++) {
            if ($mNum[$i][$i] != 0) { 
                $base_x[$i] = $i; 
            } else  { 
                $free_x[$i] = $i;
                if ($X[$i] == 1) $base_x[$i] = $i;
            }  
        }
        for ($i = COUNT_I + 1; $i <= COUNT_VAR; $i++) $free_x[$i] = $i;
        //$count_free_x = count($free_x);
    }
        
    for ($i = COUNT_I; $i >= 1; $i--) {
        if ($mNum[$i][$i] != 0) {
            if  (COUNT_ROW == COUNT_VAR)  {
                $str = "<font color='#000055'><b>Система имеет одно решение:&nbsp;&nbsp;&nbsp;число ненулевых строк равно числу неизвестных:&nbsp;&nbsp;&nbsp; {$count_row}&nbsp; =&nbsp; {$i}</b></font>\n";
                echo $str;
                $count_i = $i;
                flyBackOne($mNum, $mDen, $count_i);
                return;
            } elseif (COUNT_ROW < COUNT_VAR) {
                $COUNT_VAR = COUNT_VAR;
                $count_i = $i;
                echo "<br><font color='#000055'><b>Система имеет множество решений: число ненулевых строк меньше числа неизвестных:  {$count_row}&nbsp;< &nbsp;{$COUNT_VAR}<br>\n";
                $str = "";
                for ($j = 1, $end = end($free_x); $j <= COUNT_VAR; $j++) { 
                  if ( ( !empty($free_x[$j]) ) && ($end != $j) ) $str .= "x<sub>{$j}</sub>&nbsp;,&nbsp;&nbsp;"; 
                }
                $str .= "x<sub>{$end}</sub>&nbsp;&nbsp;";
                echo $str."-&nbsp; свободные неизвестные</b></font>\n";               
                flyBackMany($mNum, $mDen, $count_i, $free_x);
                return;
            } else {                                                                                                                                                                                                
                $str = "<font color='#000055'><b>Система несовместна</b></font>\n";
                echo $str;
                return; 
            }
        }
    }   
}

function flyBackOne($mNum, $mDen, $count_i, $xNum = array(), $xDen = array()) {
    if ( defined("SHOW_STRING") ) {} else echo "<p><b>Обратный ход Гаусса :</b></p>\n";
    for ($i = $count_i; $i >= 1; $i--) {
        $num = 0;
        $den = 1;
        for ($j = COUNT_VAR; $j >= $i; $j--) { 
           if (!empty($xNum[$j])) { 
                fraction::sum($mNum[$i][$j], $mDen[$i][$j], $num, $den);
                $num = fraction::getNumOfSum();
                $den = fraction::getdenOfSum();
           }
        }
        for ($j = COUNT_VAR; $j >= $i; $j--) {
            if (empty($xNum[$i])) {
                if ($mNum[$i][$i] != 0) {
                    fraction::minus($mNum[$i][COUNT_VAR+1], $mDen[$i][COUNT_VAR+1], $num, $den);
                    $xNum[$i] = fraction::getNumOfMinus();
                    $xDen[$i] = fraction::getDenOfMinus();
                    fraction::division($xNum[$i], $xDen[$i], $mNum[$i][$i], $mDen[$i][$i]);
                    $xNum[$i] = fraction::getNumOfDiv();
                    $xDen[$i] = fraction::getDenOfDiv();
                    fraction::simplification($xNum[$i], $xDen[$i]);
                    $xNum[$i] = fraction::getSimlNum();;
                    $xDen[$i] = fraction::getSimplDen();    
                } else { $xNum[$i] = 0; $xDen[$i] = 1; }
            }
        }
        for ($l=$i; $l >= 1; $l--) {
            $mNum[$l][$i] = $mNum[$l][$i] * $xNum[$i];
            $mDen[$l][$i] = $mDen[$l][$i] * $xDen[$i];
            fraction::simplification($mNum[$l][$i], $mDen[$l][$i]);
            $mNum[$l][$i] = fraction::getSimlNum();
            $mDen[$l][$i] = fraction::getSimplDen();
        }
        echo "<br><font color='#005300'><b>x<sub>{$i}</sub>&nbsp;=&nbsp;{$xNum[$i]}", $xDen[$i] == 1 ? "" : "/{$xDen[$i]}",":</b></font>\n";
        printM(0, $mNum, $mDen, $i);
    }
    
    echo "<br><br><font color='#003E00'><b>Решение:&nbsp;&nbsp;\n";
    for ($i=1; $i <= COUNT_VAR; $i++) {
        echo "x<sub>{$i}</sub>&nbsp;=&nbsp;{$xNum[$i]}", $xDen[$i] == 1 ? "" : "/{$xDen[$i]}",";&nbsp;&nbsp;&nbsp;\n";
    }
    echo "</b></font>\n";
} 

function flyBackMany($mNum, $mDen, $count_i, $free_x = array()) {
    echo "<p><b>Обратный ход Гаусса :</b></p>\n"; define("SHOW_STRING", TRUE);
    if ( empty($_GET['click']) ) {
        echo "<form action='action.php' method='GET'>\n";
        echo "<p>Введите проивольные значения свободным неизвестным:</p>\n";
        echo "<table border='0'>\n";
        echo "<tr>\n";
        for ($j = 1; $j <= COUNT_VAR; $j++) {
            if ( !empty($free_x[$j]) ) echo "<td nowrap><input type='text' maxlength='3' size='3' name='$j'>X<sub>$j</sub></td>\n";
        }  
        echo "<td><input type=submit name='click' value='Решить'></td>\n";
        echo "</tr>\n";  
        echo "</table>\n";
        echo "</form>\n";        
    } else {
        echo "<font color='#000055'><b>";
        for ($j = 1; $j <= COUNT_VAR; $j++) {
            if ( !empty($free_x[$j]) ) {
                fraction::setFrac($_GET[$j]);
                $xNum[$j] = fraction::get_numOfFrac();
                $xDen[$j] = fraction::get_denOfFrac();
                echo "x<sub>{$j}</sub>&nbsp;=&nbsp;{$xNum[$j]}", $xDen[$j] == 1 ? "" : "/{$xDen[$j]}","&nbsp;;&nbsp;&nbsp;";
            }
        }
            echo "</b></font><br>\n";
        for ($i = COUNT_ROW; $i>= 1; $i--) {
            for ($j = 1; $j <= COUNT_VAR; $j++) {
              if ( !empty($free_x[$j]) ) {  
                $mNum[$i][$j] = $mNum[$i][$j] * $xNum[$j];
                $mDen[$i][$j] = $mDen[$i][$j] * $xDen[$j];
                fraction::simplification($mNum[$i][$j], $mDen[$i][$j]);
                $mNum[$i][$j] = fraction::getSimlNum();
                $mDen[$i][$j] = fraction::getSimplDen();
              }  
            }
        }
        flyBackOne($mNum, $mDen, $count_i, $xNum, $xDen);
      }
} 
/*
function putInOrder(&$mNum, &$mDen) {
    for ($i = 1; $i < COUNT_EQUAT; $i++) {
        for ($m = $i + 1; $m <= COUNT_EQUAT; $m++) {
            for ($j = 1; $j <= COUNT_VAR + 1; $j++) { 
                if ( ($mNum[$m][$j] != $mNum[$i][$j]) or ($mDen[$m][$j] != $mDen[$i][$j]) ) $non_equal = TRUE; 
            }
            if (!isset($non_equal)) {
                if ($mNum[$m][$j] == 0) { continue; unset($non_equal); }  
                for ($j = 1; $j <= COUNT_VAR + 1; $j++) { $mNum[$m][$j] = 0; $mDen[$m][$j] = 1; } 
                
                echo "<br>Удалили {$m}-ую строку &nbsp;\n";
                printM(0, $mNum, $mDen);
            }
            unset($non_equal);    
        }
    }
    for ($i = 1; $i < COUNT_EQUAT; $i++) { 
            for ($j = 1; $j <= COUNT_VAR + 1; $j++) {
                if ($mNum[$i][$j] != 0) $non_zero = TRUE;
            }     
            if ( !isset($non_zero) ) {
                for ($k = $i + 1; $k <= COUNT_EQUAT; $k++) { 
                    for ($j = 1; $j <= COUNT_VAR + 1; $j++) { if ($mNum[$k][$j] != 0) $non_zero_ = TRUE; }                               
                }
                if (isset($non_zero_)) { 
                    for ($j = 1; $j <= COUNT_VAR + 1; $j++) {
                        $vector_num[$j] = $mNum[$i][$j];
                        $vector_den[$j] = $mDen[$i][$j];
                        $mNum[$i][$j] = $mNum[$i+1][$j];
                        $mDen[$i][$j] = $mDen[$i+1][$j];
                        $mNum[$i+1][$j] = $vector_num[$j];
                        $mDen[$i+1][$j] = $vector_den[$j];
                    }
                    unset($non_zero_);
                    echo "<br>Поменяли местами {$i}-е и ",$i+1,"-е уравнения&nbsp;\n";
                    printM(0, $mNum, $mDen); 
                }               
            }
            unset($non_zero); 
    }
} */   
?>

