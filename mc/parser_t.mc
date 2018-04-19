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
	a << b;
	b >> a;
	
	if(x == 0)
	{
		x = x + 1;
	}
}

def alloc(a : float) -> char
{
	return a;
}