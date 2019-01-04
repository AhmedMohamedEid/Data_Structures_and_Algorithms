# Uses python3
import sys

def get_change(m):
    coins = [10,5,1]
    while m != 0:
    	for coin in coins:
    		if (m-coin >= 0):
    			m-=coin 
    			result = result+1
    			break

    return result

if __name__ == '__main__':
    m = int(sys.stdin.read())
    print(get_change(m))
