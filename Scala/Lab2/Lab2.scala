object Lab2 {
  implicit def IntToVector(a: Int): IntVector = new IntVector(a)
  def main(args: Array[String]): Unit = {
    var vector = new Vector(1, 2, 3)
    var vector2 = new Vector(2, 3)
    println((2 * vector + vector2).toString)
    println((vector ** vector2).toString)
  }
}
