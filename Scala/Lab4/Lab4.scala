object Lab4 {
  def main(args: Array[String]): Unit = {
    val range0 = new Range[Double](-12.34, 34)
    val range1 = new Range[Double](-12.35, 35.12)
    val range2 = new Range[Double](-123, 2)
    val range3 = new Range[Double](36, 99)
    val range4 = new PointRange[Double](3.123)
    val range5 = new PointRange[Double](-11.9)
    val range6 = new PointRange[Double](-128)
    println(range1 ⊃ range0)
    println(range1 ⊃ range2)
    println(range2 ⊃ range3)
    println(range3 ⊃ range4)
    println(range2 ⊃ range5)
    println(range5 ⊃ range6)

    println((range1 ⋂ range0).toString)
    println((range1 ⋂ range2).toString)
    println((range2 ⋂ range3).toString)
    println((range3 ⋂ range4).toString)
    println((range2 ⋂ range5).toString)
    println((range5 ⋂ range6).toString)

    println((range1 ⋂ range0).length)
    println((range1 ⋂ range2).length)
    println((range2 ⋂ range3).length)
    println((range3 ⋂ range4).length)
    println((range2 ⋂ range5).length)
    println((range5 ⋂ range6).length)

    val range7 = new Range[String]("asa", "sdf")
    val range8 = new Range[String]("aaaaa", "yy")
    val range9 = new PointRange[String]("sr")
    val range10 = new PointRange[String]("yyy")
    println(range8 ⊃ range7)
    println(range7 ⊃ range9)
    println(range8 ⊃ range9)
    println(range7 ⊃ range10)

    println((range8 ⋂ range7).toString)
    println((range7 ⋂ range9).toString)
    println((range8 ⋂ range9).toString)
    println((range7 ⋂ range10).toString)

//    println((range8 ⋂ range7).length)
  }

}
