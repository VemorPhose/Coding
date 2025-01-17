https://forms.gle/k8QsW5UE8F5v4NxA7

After years of maintaining peace, Omni-man has finally shown his true nature and invaded our Earth! But this Omni-man is corrupt and loves money more than following his Supreme Leader's orders, as he plans to retire soon and live a luxurious life in Viltrum. 

You are Invincible, and true to your name you devise a plan to save your Earth. You know Omni-man's intentions and decide to offer him a huge sum of money as advised by your commander, Cecil. But, the currency of Viltrum is obviously different than Earth's.

Your task is to convert the sum of money provided to you by Cecil to the currency of Viltrum. This is done by breaking down the sum into the *least possible number* of Earth coins, converting the numbers to 8-digit-binary numbers, and converting them back *by the other dimension*, to obtain the corresponding Viltrum coins. You can then send a messenger to Omni-man with the values of the Viltrum coins in *Descending order*, and *ignoring any 0 valued coins*.

Note that the values of Earth coins are *fixed*, {100, 50, 20, 10, 5, 2, 1}


*Input:* _A single integer 'n' denoting the sum of money._

*Output:* _Each value in Viltrum Coins printed with spaces between them._


*Example:*
_Input:_ 75

_(Processing steps):_
{50, 20, 5}

0 0 0
0 0 0
1 0 0
1 1 0
0 0 0
0 1 1
1 0 0
0 0 1
_note each column is each number in binary._

{0, 0, 4, 6, 0, 3, 4, 1}
_(converting binary to decimal row-wise.)_

*Output:* 6 4 4 3 1


*Constraints:* 1 <= n < 2^8