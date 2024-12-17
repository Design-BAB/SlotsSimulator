package main

import (
	"fmt"
	"math/rand"
	"time"
)

func pullLever(coinToAdd int, emoji [6]string) int {
  results := -1
  randomNumber := rand.Intn(6) //this will give you an output of ether one or zero
  fmt.Println("Result1 : ", emoji[randomNumber])
  randomNumber2 := rand.Intn(6)
  fmt.Println("Result2 : ", emoji[randomNumber2])
  randomNumber3 := rand.Intn(6)
  fmt.Println("Result3 : ", emoji[randomNumber3])
  if randomNumber == randomNumber2 {
    results = results + 3
    fmt.Println("You have one match! You won 3 coins!")
  } else if randomNumber2 == randomNumber3{
    results = results + 3
    fmt.Println("You have one match! You won 3 coins!")
  } else if randomNumber == randomNumber2 && randomNumber2 == randomNumber3{
    results = results + 4
    fmt.Println("You have gotten all of them in a row! You won 4 coins!")
  } else if randomNumber == randomNumber3 {
    fmt.Println("You got one non-continueous match... you get your coin back.")
    results = results + 1
  }
  return results + coinToAdd
}

func main() {
	var coins int
  var enter string
  // Initialize random seed
	rand.Seed(time.Now().UnixNano())
  emoji := [6]string{"🍒", "🍊", "🫐", "🔔", "🍉", "💸"}
  fmt.Println("Hello, please enter the number of coins you would like to play with...")
	fmt.Scanln(&coins)
  for {
    if coins == 0{
      fmt.Println("You lost all of your coins! game over!")
      break
    }
	  fmt.Println("Alright! You now have ", coins, " coins.")
    fmt.Println("Press ENTER to pull the lever!")
    fmt.Scanln(&enter)
    coins = pullLever(coins, emoji)
  }	
}
