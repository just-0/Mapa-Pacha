import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Patch

# Función para asignar colores según la fila
def asignar_color(fila, total_filas):
    if fila == total_filas-1:
        return (0.0,0.0,1.0,1.0) #color azul para el más similar
    if fila == 0:
        return (0.0, 1.0, 0.0, 1.0)  # Verde si la fila es cero
    elif fila < 0.3 * total_filas:
        # < 30% color rojo claro
        return (1.0, 0.41, 0.38, fila / (total_filas * 0.3))
    elif fila < 0.6 * total_filas:
        # < 60% color rojo normal
        return (1.0, 0.0, 0.0, (fila - 0.3 * total_filas) / (total_filas * 0.3))
    else:
        # hasta 100% color rojo oscuro
        return (0.5, 0.0, 0.0, (fila - 0.6 * total_filas) / (total_filas * 0.4))


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
    legend_elements = [Patch(color='green', label='Región Seleccionada'),
                       Patch(color= 'blue', label= 'Región más Similar'),
                       Patch(color= (1.0, 0.41, 0.38,1.0), label= "0% - 30% regiones más similares"),
                       Patch(color= (1.0, 0.0, 0.0, 1.0), label= "30% - 60% regiones más similares"),
                       Patch(color= (0.5, 0.0, 0.0, 1.0), label= "60% - 100% regiones más similares"),
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
