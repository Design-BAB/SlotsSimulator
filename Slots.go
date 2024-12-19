package main

import (
	"fmt"
	"math/rand"
	"time"
)

func pullLever(coinToAdd int, emoji [7]string) int {
  results := -1
  randomNumber := rand.Intn(7) //this will give you an output of ether one or zero
  randomNumber2 := rand.Intn(7)
  randomNumber3 := rand.Intn(7)
  fmt.Println("[ ", emoji[randomNumber], " | ", emoji[randomNumber2], " | ", emoji[randomNumber3], " ]")
  if randomNumber == randomNumber2 && randomNumber != randomNumber3 {
    results = results + 3
    fmt.Println("You have one match! You won 3 coins!")
  } else if randomNumber2 == randomNumber3 && randomNumber3 != randomNumber{
    results = results + 3
    fmt.Println("You have one match! You won 3 coins!")
  } else if randomNumber == randomNumber2 && randomNumber2 == randomNumber3{
    if randomNumber == 5 || randomNumber == 6{
      results = results + 10
      fmt.Println("Jackpot! You won 10 coins!")
    } else {
      fmt.Println("You got all of them to match! You get 5 coins!")
      results = results + 5
    }
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
  emoji := [7]string{"🍒", "🍊", "🫐", "🔔", "🍉", "💸", "💎"}
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
