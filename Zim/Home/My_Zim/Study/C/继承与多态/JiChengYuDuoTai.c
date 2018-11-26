#include <stdio.h>
#include <string.h>

// Animal
struct animal
{
	char name[20];
	void (*Speak)();
};


// Animal::Animal(const char*name,void(*fun)())
void Animal(struct animal*this,const char*name,void(*fun)())
{
	strcpy(this->name,name);
	this->Speak=fun;
}

// Animal::Introduce()
void Introduce(struct animal*this)
{
	printf("I'm a %s.\n",this->name);
}

// Cat:Animal
struct cat
{
	struct animal base;
	char color[20];
};

// Cat::Speak()
void CatSpeak()
{
	printf("miao miao miao miao miao?????\n");
}

// Cat::Cat(const char*color)
void Cat(struct cat*this,const char*color)
{
	Animal((struct animal*)this,"cat",CatSpeak);
	strcpy(this->color,color);
}

// Cat::ShowColor()
void ShowColor(struct cat*this)
{
	printf("I'm a %s cat.\n",this->color);
}

// Dog:Animal
struct dog
{
	struct animal base;
};

// Dog::Speak()
void DogSpeak()
{
	printf("wang!wang!wang!\n");
}

// Dog::Dog()
void Dog(struct dog* this)
{
	Animal((struct animal*)this,"dog",DogSpeak);
}


int main()
{
	struct cat white_cat,black_cat;
	struct dog doge;
	
	Cat(&white_cat,"white");
	Cat(&black_cat,"black");
	Dog(&doge);

	struct animal* animals[]={&white_cat,&black_cat,&doge};
	for(int i=0;i<3;i++)
	{
		Introduce(animals[i]);
		animals[i]->Speak();
	}
	ShowColor(&white_cat);
	ShowColor(&black_cat);
	return 0;
}