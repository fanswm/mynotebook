#include <stdio.h>
#include <stddef.h>

#define FordCar2Car(a) ((Car*)&(a->car))
#define FordCar2ForSale(a) ((ForSale*)&(a->sale))
#define Car2FordCar(a) ((FordCar*)a)
#define ForSale2FordCar(a) ( (FordCar*) ( ((char*)a) - offsetof(FordCar,sale) ) )


typedef struct car
{
    int max_speed;
}Car;

typedef struct for_sale
{
    int price;
}ForSale;

typedef struct ford_car
{
    Car car;
    ForSale sale;
}FordCar;

void drive(Car* this)
{
    printf("I can drive at the speed of %d kilometers per hour\n",this->max_speed);
}

void sale(ForSale* this)
{
    printf("The price is %d yuan\n",this->price);
}

void ford_car_sale(FordCar* this)
{
    printf("The ford car will cost you %d yuan,\nand it can drive at the speed of %d kilometers per hour\n",
        this->car.max_speed,
        this->sale.price);
}

int main()
{
    FordCar A;
    A.car.max_speed=120;
    A.sale.price=500000;

    printf("-------------------------------------------------\n");
    // base class->subclass
    FordCar*pford=&A;
    sale(FordCar2ForSale(pford));
    drive(FordCar2Car(pford));
    printf("-------------------------------------------------\n");
    // subclass->base class
    Car* pcar=FordCar2Car(pford);
    ForSale* pfor_sale=FordCar2ForSale(pford);
    ford_car_sale(Car2FordCar(pcar));
    ford_car_sale(ForSale2FordCar(pfor_sale));
    return 0;
}