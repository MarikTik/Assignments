import turtle
import random

screen = turtle.Screen()
t = turtle.Turtle()

def picasso_draw():
    t.speed(100)
    t.goto(t.xcor(), - 300)
    for i in range(-300, 250, 10):
        t.circle(random.uniform(10, 100))
        t.goto(t.xcor(), i)
    
    t.up()
    t.goto(200, -300)
    t.down()
    t.color("red")

    for i in range(-300, 250, 10):
        t.goto(i + random.uniform(0, 10), i+ random.uniform(0, 10))
    
    t.color("blue")

    for i in range(300, -250, -10):
        t.goto(i - random.randint(10, 15), i- random.randint(-20, -10))

    # notice that lines are also shapes))
def main():
    picasso_draw()
    input()

main()