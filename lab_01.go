package main

import (
	"fmt"
	"math"
	"time"
)

func Iterative(n int) uint64 {
	if n == 1 {
		return 0
	} else if n == 2 {
		return 1
	}
	var fibbonaci = [2]uint64{0, 1}
	var result uint64
	for i := 2; i < n; i++ {
		result = fibbonaci[0] + fibbonaci[1]
		fibbonaci[0] = fibbonaci[1]
		fibbonaci[1] = result
	}
	return result
}
func Recursive(n int) int64 {
	if n == 1 {
		return 0
	} else if n == 2 {
		return 1
	}
	return Recursive(n-1) + Recursive(n-2)
}
var cache [100]uint64
func OptimizedRecursive(n int, a *[100]uint64) uint64 {
    if n == 1 || n == 2 {
		return 1
	}
    if cache[n] != 0 {
        return cache[n]
	}
    cache[n] = OptimizedRecursive(n - 1, &cache) + OptimizedRecursive(n - 2, &cache)
	return cache[n]
}
func OldBinet(n int) int64 {
	var a float64 = math.Pow(1 + math.Sqrt(5), float64(n));
	var b float64 = math.Pow(1 - math.Sqrt(5), float64(n));
	return int64( (a - b) / (math.Pow(2, float64(n)) * math.Sqrt(5)) )
}
func Binet(n int) int {
	sqrt5 := math.Sqrt(5)
	phi := (1 + sqrt5) / 2

	return int(math.Round(math.Pow(phi, float64(n)) / sqrt5))
}
func MatrixExponentiation(n int) uint64 {
    var base = [2][2]uint64{{1, 1},{1, 0}}
	  return MatrixPower(base, n)[0][1];
}
func MatrixPower(base [2][2]uint64, n int) [2][2]uint64 {
	var ans = [2][2] uint64{{1, 0},{0, 1}}
	  for n != 0 {
		  if (n & 0x1) > 0 {
			ans = MultMat(ans, base)
		  }
		  base = MultMat(base, base)
		  n >>= 1;
	  }
	  return ans;
}
func MultMat (a [2][2]uint64, b[2][2]uint64) [2][2]uint64 {
	var c [2][2]uint64
	for i := 0; i < 2; i++ {
		for j := 0; j < 2; j++	 {
			c[i][j] = 0
			for k := 0; k < 2; k++ {
				c[i][j] += a[i][k] * b[k][j]
			}
		}
	}
	return c
}
func FastDoubling(n int) [2]uint64 {
	if n == 0 {
		return [2]uint64{0, 1}
	}
	var pair [2]uint64 = FastDoubling(n >> 1)
	var a uint64 = pair[0] * (2 * pair[1] - pair[0])
	var b uint64 = pair[0] * pair[0] + pair[1] * pair[1]
	if (n & 0x1) > 0 {
		return [2]uint64{b, a + b}
	} else {
		return [2]uint64{a, b}
	}
}

var input_set_01 = []int32{5, 7, 10, 12, 15, 17, 20, 22, 25, 27, 30, 32, 35, 37, 40, 42, 45}
var input_set_02 = []int32{501, 631, 794, 1000, 1259, 1585, 1995, 2512, 3162, 3981, 5012, 6310, 7943, 10000, 12589, 15849}

var output_set_01 [17]float64
var output_set_02 [16]float64
var output_set_03 [27]float64

func main() {
	for i := 0; i < 12; i++ {
		//fmt.Println(i + 1, MatrixExponentiation(i + 1))
	}

	//os.Exit(1)

	for a := 0; a < len(input_set_02); a++ {
		start_time := time.Now()

		var nr_of_tests int = 10000000
		for i := 0; i < 100; i++ {
			//FastDoubling(int(input_set_02[a]));

			OptimizedRecursive(int(input_set_02[a]), &cache)
			//for j := 0; j < 100; j++ {
			//	cache[j] = 0
			//}
		}

		end_time := time.Now()
		execution_time := end_time.Sub(start_time)
		var start int64 = int64(start_time.UnixMicro())
		var end int64 = int64(end_time.UnixMicro())
		var diff float64 = float64(end) - float64(start)
		diff = diff / float64(nr_of_tests)
		var one_time int64 = execution_time.Nanoseconds() / int64(nr_of_tests)
		fmt.Printf("Execution time: %v\n", execution_time)
		fmt.Println("One time execution: \n", one_time)

		output_set_02[a] = diff
	}
	for a := 0; a < len(input_set_02); a++ {
		fmt.Printf("%f, ", output_set_02[a])
	}
}