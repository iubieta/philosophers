# Permitir cualquier configuracion
set auto-load safe-path /

# Configuración de estilo y salida
set confirm off
set pagination off
set style enabled on
set print pretty on

# Establecer argumentos del programa
set args 4 100 200 300 5 

# Añadir un directorio de búsqueda

# Poner breakpoints específicos
break main
break notify_status

# Watchpoint para ver cambios en una variable
#watch variable_importante

# Ejecutar el programa automáticamente
run

