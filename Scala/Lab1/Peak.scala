object Peak {
  def main(args: Array[String]): Unit = {

    val new_peaks : (List[Int], Int) => List[Int] = {
      case (x1::x2::x3::rest, a) if (x2> x1 & x2>x3) => (a+1)::new_peaks(x2::x3::rest, a+1)
      case (x1::x2::x3::rest, a) => new_peaks(x2::x3::rest, a+1)
      case _ => Nil
    }

    val peaks : List[Int] => List[Int] = {
      list => new_peaks(list, 0)
    }

    val p = peaks(List(1,2,3,2,1,0,2,3,4,2))

    val p1 = peaks(List(1))
  }
}
