make:
	g++ main.cpp bitmap.cpp -o main

clean:
	rm -f main
	rm -f copy.bmp

pika:
	./main -i pikachu.bmp copy.bmp

pikaCell:
	./main -c pikachu.bmp copy.bmp

pikaGray:
	./main -g pikachu.bmp copy.bmp

pikaPixel:
	./main -p pikachu.bmp copy.bmp

pikaBlur:
	./main -b pikachu.bmp copy.bmp

24:
	./main -i simple24.bmp copy.bmp

32:
	./main -i simple32.bmp copy.bmp
