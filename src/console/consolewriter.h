#include <iostream>
#include <string>

#include <inttypes.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <ncurses.h>
#endif

class ConsoleWriter {

private:
    int maxrow;
    int maxcol;

public:
    ConsoleWriter() {
        #ifdef _WIN32
            // Obtener el handle de la consola en Windows
            consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

            // Obtener la información de la consola
            CONSOLE_SCREEN_BUFFER_INFO screenInfo;
            GetConsoleScreenBufferInfo(consoleHandle, &screenInfo);
            originalAttributes = screenInfo.wAttributes;
        #else
            // Inicializar la biblioteca ncurses en Ubuntu
            initscr();
            start_color();
            cbreak();
            noecho();
            keypad(stdscr, TRUE);
            curs_set(0);
            getmaxyx( stdscr, maxcol, maxrow );

            
        #endif
    }

    int getmaxcol(){
        return maxcol;
    }

    int getmaxrow(){
        return maxrow;
    }

    ~ConsoleWriter() {
        #ifdef _WIN32
            // No se requiere limpieza adicional en Windows
        #else
            // Finalizar la biblioteca ncurses en Ubuntu
            endwin();
        #endif
    }

    void write( int row, int col, const std::string& text, int foregroundColor = COLOR_WHITE, int backgroundColor = 0) {
        #ifdef _WIN32
            // Obtener el handle de la consola en Windows
            HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

            // Obtener los atributos actuales de la consola
            CONSOLE_SCREEN_BUFFER_INFO screenInfo;
            GetConsoleScreenBufferInfo(consoleHandle, &screenInfo);
            WORD originalAttributes = screenInfo.wAttributes;

            // Calcular los nuevos atributos basados en los colores especificados
            WORD newAttributes = originalAttributes;
            if (foregroundColor != 0) {
                newAttributes &= 0xFFF0;  // Borrar los bits de primer plano existentes
                newAttributes |= foregroundColor;  // Establecer los nuevos bits de primer plano
            }
            if (backgroundColor != 0) {
                newAttributes &= 0xFF0F;  // Borrar los bits de fondo existentes
                newAttributes |= (backgroundColor << 4);  // Establecer los nuevos bits de fondo
            }

            // Establecer la posición del cursor en Windows
            COORD newPos = { static_cast<short>(x), static_cast<short>(y) };
            SetConsoleCursorPosition(consoleHandle, newPos);

            // Establecer los nuevos atributos en Windows
            SetConsoleTextAttribute(consoleHandle, newAttributes);

            // Escribir el texto en la posición especificada en Windows
            std::cout << text;

            // Restaurar los atributos originales en Windows
            SetConsoleTextAttribute(consoleHandle, originalAttributes);
        #else
            
            // Definir pares de colores personalizados
            //init_pair(1, foregroundColor, backgroundColor);

            // Establecer los atributos del texto

            init_pair(1, COLOR_WHITE, COLOR_BLACK);
            init_pair(2, COLOR_RED,COLOR_BLACK);
            if (foregroundColor!=COLOR_WHITE){
                attron(COLOR_PAIR(2));
            }else {
                attron(COLOR_PAIR(1));
            }
            // Establecer la posición del cursor en Ubuntu
            move(row, col);

            // Imprimir el texto en la posición especificada en Ubuntu            
            addstr(text.c_str());

            // Restaurar los atributos del texto en Ubuntu
            if (foregroundColor!=COLOR_WHITE){
                attroff(COLOR_PAIR(2));
            }else {
                attroff(COLOR_PAIR(1));
            }

            // Actualizar solo la línea escrita en Ubuntu
            refresh();
        #endif
    }

    void clearScreen() {
        #ifdef _WIN32
            // Limpiar la pantalla en Windows
            COORD topLeft = { 0, 0 };
            CONSOLE_SCREEN_BUFFER_INFO screenInfo;
            DWORD written;

            GetConsoleScreenBufferInfo(consoleHandle, &screenInfo);
            FillConsoleOutputCharacter(consoleHandle, ' ', screenInfo.dwSize.X * screenInfo.dwSize.Y, topLeft, &written);
            FillConsoleOutputAttribute(consoleHandle, screenInfo.wAttributes, screenInfo.dwSize.X * screenInfo.dwSize.Y, topLeft, &written);
            SetConsoleCursorPosition(consoleHandle, topLeft);
        #else
            // Limpiar la pantalla en Ubuntu
            clear();
            refresh();
        #endif
    }


    char getchr(){

        char str = getch();
        return str;
    }

    int getwchr(){

        int str = wgetch(stdscr);
        return str;
    }

    int readInt() {

        nocbreak();
        echo();

        int value = 0;
        
        scanw("%d", &value);

        cbreak();
        noecho();

        return value;
    }

    double readDouble() {
        nocbreak();
        echo();

        double value = 0.0;
        
        scanw("%lf", &value);

        cbreak();
        noecho();
        return value;
    }

    std::string readString() {
        nocbreak();
        echo();

        std::string value;
        
        char buffer[256];
        getstr(buffer);
        value = buffer;
        cbreak();
        noecho();
        return value;
    }

    char createMenu(std::string title, std::string optionsMenu[], int numoptions, int row, int col){
        char opcion;
        int x,y;
        
        while (true) {
            clearScreen();  // Limpiar la pantalla
            x =col;
            y=row;

            // Mostrar el menú
            write(y,x, title);
            y++;
            y++;
            
           
            for (int i=0; i< numoptions; i++){
                write(y+i, x, optionsMenu[i]);

            }
            
            // Leer la opción seleccionada
            //std::cin >> opcion;
            opcion = getchr();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar el salto de línea
            char max = numoptions+'0';
            if (opcion>= '1' && opcion <=max){
                return opcion;
            }
            else
            {
                write(row+numoptions+5, col, "Opción inválida. Por favor, seleccione una opción válida.");
                // Esperar a que el usuario presione una9 tecla para continuar
                #ifdef _WIN32
                    //std::cout << "Presione cualquier tecla para continuar...";
                    _getch();
                #else
                    //std::cout << "Presione Enter para continuar...";
                    getch();
                    
                #endif
            }
            
        }

    }

private:
    #ifdef _WIN32
        HANDLE consoleHandle;
        WORD originalAttributes;
    #endif
    
};