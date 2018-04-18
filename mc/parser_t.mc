#Parser Test program

var x : int = 0;
var y : float = 3;
let HELLO : char = 'a';

def main(a : int, b : float) -> int
{
	alloc(alloc(x));
	x = a + b;
	a + b;
	y = b - a;
	return a;
}

def alloc(a : float) -> char
{
	return a;
}