import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Patch

# Función para asignar colores según la fila
def asignar_color(fila, total_filas):
    if fila == 0:
        return (0.545, 0.0, 0.0, 1.0) # Darkblue para la "región seleccionada"
    else:
        intensidad = fila / (total_filas - 1)  # Normalizar intensidad para las demás regiones
        return (1.0, 0.0, 0.0, intensidad)

# Función para leer el archivo cuadrantes.txt
def leer_cuadrantes(archivo):
    datos = np.loadtxt(archivo, delimiter=',')
    return datos

# Función para leer el archivo meteorite_clean_test.csv
def leer_meteoritos(archivo):
    datos = np.genfromtxt(archivo, delimiter=';', skip_header=1, usecols=(1, 2))
    return datos

# Función para graficar los cuadrantes y los puntos
# Función para graficar los cuadrantes y los puntos
def graficar_cuadrantes_y_puntos(datos_cuadrantes, datos_meteoritos):
    total_filas = datos_cuadrantes.shape[0]

    fig, ax = plt.subplots()

    for i in range(total_filas):
        x, y, h = datos_cuadrantes[i]
        color = asignar_color(i, total_filas)
        if(i== 0):
            rect = plt.Rectangle((x, y), h, h, linewidth=0.5, edgecolor='black', facecolor=color, label=f'Región {i}', zorder=2)
        else:
            rect = plt.Rectangle((x, y), h, h, linewidth=0.5, edgecolor='black', facecolor=color, label=f'Región {i}')
        ax.add_patch(rect)

    # Agregar puntos
    ax.scatter(datos_meteoritos[:, 0], datos_meteoritos[:, 1], color='black', marker='o', s=1, label='Puntos Meteoritos', zorder=3)

    ax.set_xlim([-200.00, 400.00])
    ax.set_ylim([-200.00, 400.00])

    plt.xlabel('Coordenada X')
    plt.ylabel('Coordenada Y')
    plt.title('Mapa-Pacha')

    plt.grid(True, linestyle='--', alpha=0.7)
    plt.gca().set_aspect('equal', adjustable='box')  # Asegura que los ejes tengan la misma escala

    # Agregar leyenda solo para "Región Seleccionada" y leyenda personalizada fuera del plano cartesiano
    legend_elements = [Patch(color='darkred', label='Región Seleccionada'),
                       Patch(color='lightcoral', label='Regiones menos similares'),
                       Patch(color='red', label='Regiones más similares'),
                       plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='black', markersize=5, label='Coordenadas de los Meteoritos', linestyle='None')]

    plt.legend(handles=legend_elements, loc='upper right', bbox_to_anchor=(1.25, 1.0))

    plt.show()

# Nombre del archivo cuadrantes.txt
archivo_cuadrantes = 'cuadrantes.txt'

# Nombre del archivo meteorite_clean_test.csv
archivo_meteoritos = 'meteorite_clean_test.csv'

# Leer los datos del archivo cuadrantes.txt
datos_cuadrantes = leer_cuadrantes(archivo_cuadrantes)

# Leer los datos del archivo meteorite_clean_test.csv
datos_meteoritos = leer_meteoritos(archivo_meteoritos)

# Graficar los cuadrantes y los puntos
graficar_cuadrantes_y_puntos(datos_cuadrantes, datos_meteoritos)
