package main

import (
	"fmt"
)

type lru struct{
	list []int
	head int
	tail int
	cap  int
	have bool
}

func (l *lru) put(n int){
	i := l.head
	for {
		if l.list[i] == n {
			t := i
			j := (i+1)%l.cap
			for {
				if j == l.tail {
					l.list[t] = n
					return
				}else {				
					l.list[t] = l.list[j]
				}
				t = j
				j = (j+1)%l.cap
			}
		}
		i = (i+1)%l.cap
		if i == l.tail {
			l.list[i] = n
			l.tail = (l.tail + 1)%l.cap
			if i == l.head && l.have {
				l.head = (l.head+ 1)%l.cap
			}
			l.have = true
			return
		}
	}
}

func (l *lru) print (){
	i := l.head
	for {
		fmt.Print(l.list[i])
		i = (i+1)%l.cap
		if i == l.tail {
			break
		}
	}
	fmt.Println()
}


func main() {
	l := &lru{list:make([]int, 3, 3), cap:3}
	l.list[0] = -1
	l.list[1] = -1
	l.list[2] = -1
	//7 0 1 2 0 3 0 4
	l.put(7)
	l.print()
	l.put(0)
	l.print()
	l.put(1)
	l.print()
	l.put(2)
	l.print()
	l.put(0)
	l.print()
	l.put(3)
	l.print()
	l.put(0)
	l.print()
	l.put(4)
	l.print()
}
