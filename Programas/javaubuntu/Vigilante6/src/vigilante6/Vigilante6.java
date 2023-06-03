package vigilante6;

/* Vigilante.java

    AGENTE REACTIVO

2003 07 Jesus Olivares
 */
import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;
import java.util.StringTokenizer;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;

/*
1. Comentar los métodos dibujar, borrar, mover de Serpiente()
2. Colocar el método mover que se hizo en el pizarrón
3. Comentar el while(viva == true) y su llave que cierra }
4. Modificar graf.matriz[renS + movR[dir[imov]]][colS + movC[dir[imov]]] = id; 
   que no actualizan renS y colS por las líneas que sí lo hacen:
   renS += movR[dir[imov]];
   colS += movC[dir[imov]];
   graf.matriz[renS][colS] = id;
ADICIONAL:
5. 
 */
class Serpiente {
    static byte idNumero = 0; // CONTADOR DE CUANTAS SERPIENTES HAY (GLOBAL) 
    byte id; // IDENTIFICADOR DE LA SERPIENTE
    int t = 0;  // TAMAÑO INICIAL
    int renS = 0, colS = 0; // REN Y COL DE LA SERPIENTE
    int renMax, colMax; // LIMITE DE MOVIMIENTO DE LA SERPIENTE
    Grafica graf; // TABLERO DONDE SE MUEVEN LAS SERPIENTES

    int renHistoria[] = new int[5]; // HISTORIA DE LA SERPIENTE PARA BORRARLA
    int colHistoria[] = new int[5]; // HISTORIA DE LA SERPIENTE
    int iHistoria = 0;
    boolean viva = false; // INDICA SI LA SERPIENTE ESTA VIVA O NO
    
    Serpiente(Grafica grafica) { // CONSTRUCTOR DE LA SERPIENTE
        idNumero++;
        this.id = idNumero;
        System.out.println("id=" + id);
        graf = grafica; // LA SERPIENTE ACTUAL APUNTA AL TABLERO
        renMax = graf.renMax; // TOMA LIMITE DE RENGLONES DEL TABLERO
        colMax = graf.colMax; // TOMA LIMITE DE COLUMNAS DEL TABLERO 

        // GENERA UNA POSICIÓN DE LA SERPIENTE EN UNA POSICIÓN LIBRE
        boolean libre = false;
        while (libre == false) {
            renS = new Random().nextInt(renMax);
            colS = new Random().nextInt(colMax);
            if (graf.matriz[renS][colS] == 0) {
                libre = true;
            }
        }
        graf.matriz[renS][colS] = id;
        renHistoria[0] = renS;
        colHistoria[0] = colS;
        iHistoria = 1;
        t = 1; // INICIA EN TAMAÑO UNO
        viva = true;
    }

    void mover() {
        int dir[] = new int[4];
        int otro;
        boolean repetido;        
        int movR[] = {0, 1, 0, -1}; // DER, ABAJO, IZQ, ARRIBA
        int movC[] = {1, 0, -1, 0};

        System.out.print("id="+id+" viva="+viva);
        if( viva == false ) {
            System.out.println("");
            return;
        }
        System.out.println(" ("+renS+", "+colS+")");
        
        // DETERMINAR MOVIMIENTO VALIDO
        Random rand = new Random();
        dir[0] = rand.nextInt(4);
        for (int i = 1; i < 4; i++) {
            do {
                otro = rand.nextInt(4);
                repetido = false;
                for (int j = 0; j < i; j++) {
                    if (otro == dir[j]) {
                        repetido = true;
                    }
                }
            } while (repetido == true);
            dir[i] = otro;
        }
        // PINTA LOS MOVIMIENTOS VÁLIDOS
        System.out.println(""+dir[0]+" "+dir[1]+" "+dir[2]+" "+dir[3]);
        
        boolean encontro = false;  // SUPONEMOS QUE NO HAY LUGAR LIBRE
        for (int imov = 0; (imov < 4) && (encontro == false); imov++) {
            int renAux = renS + movR[dir[imov]];
            int colAux = colS + movC[dir[imov]];
            System.out.println("MOVER A: "+renAux+" "+colAux);
            if ( renAux > -1 && colAux > -1 && renAux < renMax && colAux < colMax && graf.matriz[renAux][colAux] == 0) {
                encontro = true;
                System.out.println("MOV="+dir[imov]);
                renS += movR[dir[imov]];
                colS += movC[dir[imov]];
                graf.matriz[renS][colS] = id;
                if (t < 4) {
                    t += 1;
                    renHistoria[iHistoria] = renS;
                    colHistoria[iHistoria] = colS;
                    iHistoria++;
                } else {
                    // BORRA LA ULTIMA POSICION DE LA VIBORA
                    //5  6  7  8 9
                    //4  4  4  4 4 
                    // BORRAR EN EL TABLERO LA COLITA DE LA VIBORA
                    graf.matriz[renHistoria[0]][colHistoria[0]] = 0;

                    // BORRA EN LA HISTORIA DE LA VIBORA SU COLITA
                    for (iHistoria = 1; iHistoria < 4; iHistoria++) {
                        renHistoria[iHistoria - 1] = renHistoria[iHistoria];
                        colHistoria[iHistoria - 1] = colHistoria[iHistoria];
                    }
                    renHistoria[3] = renS;
                    colHistoria[3] = colS;
                }
            }
        }
        if( encontro == false ){ // SI NO ENCONTRÓ UN LUGAR LIBRE, ESTÁ BLOQUEADA
            // DESAPARECE LA VIBORA
            for (iHistoria = 0; iHistoria < t; iHistoria++) {
                // DESAPARECER LA VÍBORA CONSISTE EN COLOCAR CERO EN SU ÚLTIMA HISTORIA
                graf.matriz[renHistoria[iHistoria]][colHistoria[iHistoria]] = 0;
            }
            viva = false;
        }
    }
}

class Grafica extends Canvas {

    int yRaton;
    int xRaton;

    int resolucion;
    int renMax;
    int colMax;
    byte[][] matriz;
    Graphics gra;
    
    Color colores[] = {null, Color.MAGENTA, Color.blue, Color.green, Color.orange, Color.cyan};


    // EL METODO PAINT SE LLAMA AUTOMATICAMENTE
    public void paint(Graphics g) {
 
        setBackground(Color.white);
        g.setColor(Color.blue);
        g.drawRect(20, 20, 256, 256);
        carga("laberinto.txt");
        gra = getGraphics();
    }

    void carga(String nomArch) {
        try {
            BufferedReader entrada = new BufferedReader(new FileReader(nomArch));

            // TOMA LA RESOLUCIÓN DEL ARCHIVO
            String linea = entrada.readLine();
            resolucion = Integer.parseInt(linea);

            // CARGA LOS DATOS EN LA matriz
            int ren = 0, col = 0;
            renMax = resolucion;
            colMax = resolucion;
            matriz = new byte[resolucion][resolucion];

            // CARGA DATOS
            while (entrada.ready()) {
                linea = entrada.readLine();

                StringTokenizer punto = new StringTokenizer(linea, " ");
                col = 0;
                while (punto.hasMoreTokens()) {
                    String unPunto = punto.nextToken();
                    if (col == resolucion) {
                        continue;
                    }
                    matriz[ren][col] = (byte) Integer.parseInt(unPunto);
                    col++;
                }
                ren++;
            }

            Graphics g = getGraphics();
            // DESPLIEGA EL TABLERO
            int pps = 256 / resolucion;
            g.setColor(Color.blue);
            g.drawRect(20, 20, resolucion * pps + 1, resolucion * pps + 1);

            for (ren = 0; ren < renMax; ren++) {
                for (col = 0; col < colMax; col++) {
                    switch (matriz[ren][col]) {
                        case 0:
                            g.setColor(Color.white);
                            break;
                        case 9:
                            g.setColor(Color.darkGray);
                            break;
                    }
                    g.fillRect(20 + col * pps + 1, 20 + ren * pps + 1, pps, pps);
                }
            }

            // CIERRA EL ARCHIVO
            entrada.close();
        } catch (IOException ex) {
        }
    }

    void pintar() {
        int ren, col;
        int pps = 256 / resolucion;

        Graphics gr = getGraphics();
        gr.setColor(Color.blue);
        gr.drawRect(20, 20, resolucion * pps + 1, resolucion * pps + 1);

        for (ren = 0; ren < renMax; ren++) {
            for (col = 0; col < colMax; col++) {
                switch (matriz[ren][col]) {
                    case 0:
                        gr.setColor(Color.white);
                        break;
                    case 9:
                        gr.setColor(Color.darkGray);
                        break;
                    default:
                        gr.setColor(colores[matriz[ren][col]]);
                        break;
                }
                gr.fillRect(20 + col * pps + 1, 20 + ren * pps + 1, pps, pps);
            }
        }
    }
}

class Agente extends JFrame implements Runnable {

    Grafica grafica = new Grafica();
    Thread hilo;
    int xRaton, yRaton;
    JButton iniciar = new JButton("INICIAR");
    JButton detener = new JButton("DETENER");
    JButton salir = new JButton("SALIR");

// PANELES PARA LA PANTALLA
    JScrollPane panelScroll = new JScrollPane(grafica);
    JPanel panelBotones = new JPanel(new FlowLayout());
    JSplitPane panelAjustable = new JSplitPane(JSplitPane.VERTICAL_SPLIT);

// ACCIONES
    ActionListener accion = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            if (e.getActionCommand().equals("INICIAR")) {
                hilo.start();
            }
            if (e.getActionCommand().equals("DETENER")) {
                hilo.stop();
            }
            if (e.getActionCommand().equals("SALIR")) {
                System.exit(0);
            }
        }
    };

    // CONSTRUCTOR
    public Agente() {
        Container cont = getContentPane();

        hilo = new Thread(this);

        // ASIGNA LOS COMPONENTES EN EL PANEL DE BOTONES
        panelBotones.add(iniciar);
        panelBotones.add(detener);
        panelBotones.add(salir);

        // COLOCA LOS PANELES EN LA PANTALLA
        panelScroll.setPreferredSize(new Dimension(400, 400));
        panelScroll.setMinimumSize(new Dimension(300, 300));
        panelAjustable.add(panelScroll);
        panelAjustable.add(panelBotones);

        // AGREGA EL panelAjustable EN EL PANEL PRINCIPAL CENTRADO
        cont.setLayout(new BorderLayout());
        cont.add(panelAjustable, BorderLayout.CENTER);

        // ASIGNA LAS ACCIONES
        iniciar.addActionListener(accion);
        detener.addActionListener(accion);
        salir.addActionListener(accion);

        // ACCION PARA CUANDO SE PIDE EL CIERRE DE LA VENTANA
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });

    }

    public void run() {
        System.out.println("inicia el movimiento de las serpientes");
        Serpiente s1 = new Serpiente(grafica);
        Serpiente s2 = new Serpiente(grafica);
        Serpiente s3 = new Serpiente(grafica);
        Serpiente s4 = new Serpiente(grafica);
        Serpiente s5 = new Serpiente(grafica);
   
                
        while (true) {
            try {
                grafica.pintar();
                Thread.sleep(200); // SE CAMBIA LA VELOCIDAD, MENOR MÁS VELOCIDAD
                s1.mover();
                s2.mover();
                s3.mover();
                s4.mover();
                s5.mover();
           
            } catch (Exception e) {
            }
        }
    }
}

public class Vigilante6 {

    public static void main(String args[]) {
        Agente agente = new Agente();

        agente.setSize(500, 500);
        agente.setVisible(true);
    }
}
