
// function returning the max between two numbers 
int max(int num1, int num2)
{
	int result;

  if(num1 > num2)
		{
    	result = num1;
		}
   else 
   	{
   		result = num2;
   	}

  return result;   
}


int main()
{  
	int number1;
	int number2;
	int i;
		
	number1 = 3;
	number2 = 8;
  
  Printf("G version %s\n", "0.0.0");

  Printf("De %d y %d el mayor es %d \n", number1, number2, max(number1, number2));

  Printf("Numeros aleatorio de 1 a 100: \n");
  for (i = 0; i < 10; i++)
  	{
    	//Printf("%d ", RandBetween(1,100));
    	Printf("%d ", i);
    } 
 
	TracePrintColor(1, "Prueba de envio %d con cadena %s", 10, "hola radiola"); 
  
  Printf("\nIntroduce una tecla:"); 
  Printf("[%c]\n", GetChar());
}


