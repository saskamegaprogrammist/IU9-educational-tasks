import scala.math.sqrt
import scala.math.pow

class Vector(inCoords: Int*) {
  var coords = inCoords
  def dimension() = coords.length
  def getCoords() = coords
  def length() = sqrt(coords.map(a => pow(a, 2)).sum.toInt)

  def + (vector: Vector):Vector = {
        try {
          if (vector.dimension != dimension) {
            throw new Exception("wrong dimension")
          }
          if (vector.dimension != dimension) {
            println("wrong dimension")
          }
          new Vector(coords.zip(vector.coords).map(a => a._1+ a._2) :_*)

        }
        catch {
          case e: Exception => println("exception caught: " + e)
            this
        }
  }

  def * (value: Int) = new Vector(coords.map(a=>value*a) : _*)
  def unary_- = this * (-1)
  def - (vector: Vector) = this + (-vector)
  def ** (vector: Vector) = {
    coords.zip(vector.coords).map(a => a._1*a._2).sum
  }

  override def toString: String = coords.mkString(",")
}
