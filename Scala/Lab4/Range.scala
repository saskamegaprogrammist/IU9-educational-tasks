class Range [T:Ordering] (val start:T, val end:T) {
  var ordRange: Ordering[T] = implicitly[Ordering[T]]
  if (this.start != null) {
    if (ordRange.gt(this.start,this.end)) throw new Exception("end is greater than start");
    if (ordRange.eq(this.start,this.end)) throw new Exception("create PointRange");
  }

  def ⊃ (inRange: Range[T]): Boolean =
    if (inRange.start==null) true
    else ordRange.lteq(this.start,inRange.start) && ordRange.gteq(this.end,inRange.end)
  def ⊃ (inVal: T): Boolean =
    ordRange.lteq(this.start,inVal) && ordRange.gteq(this.end,inVal)
  def ⋂ (inRange: Range[T]): Range[T] =
    if (this ⊃ inRange) inRange
    else if (inRange ⊃ this) this
    else if (ordRange.gt(this.start, inRange.end) || ordRange.gt(inRange.start, this.end)) new EmptyRange[T]
    else if (ordRange.eq(this.start, inRange.end)) new PointRange[T](this.start)
    else if (ordRange.eq(inRange.start, end)) new PointRange[T](this.end)
    else if (ordRange.gteq(inRange.start, this.start)) new Range[T](inRange.start, this.end)
    else new Range[T](this.start, inRange.end)

  def length() (implicit num : Numeric[T]): T =
    num.minus(end,start)
  def this() = this(null.asInstanceOf[T],null.asInstanceOf[T])
  def this(point: T) = this(point,point)

  override def toString: String = start.toString + " - " + end.toString
}

class PointRange [T:Ordering] (val point:T) extends Range (point) {
  override def ⊃(inRange: Range[T]): Boolean = false
  def ⊃ (inRange: PointRange[T]): Boolean =
    ordRange.eq(this.point,inRange.point)
  override def ⊃(inVal: T): Boolean =
    ordRange.lteq(this.start,inVal)
  override def length()(implicit num : Numeric[T]): T =
    num.one
  override def toString: String = start.toString
}
class EmptyRange  [T:Ordering] extends Range {
  override def ⊃(inRange: Range[T]): Boolean = false
  override def ⊃(inVal: T): Boolean = false
  override def ⋂(inRange: Range[T]): Range[T] = new EmptyRange[T]
  override def length()(implicit num : Numeric[T]): T =
    num.zero
  override def toString: String = "empty range"
}