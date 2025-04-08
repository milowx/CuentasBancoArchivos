const int TAM = 500;

const char NOMBRES_M[100][50]={"Mateo", "Santiago", "Sebastián", "Valentino", "Emiliano", "Gabriel", "Leonardo", "Joaquín", "Andrés", "Diego",
"Antonio", "Luis", "Fernando", "Ricardo", "Alejandro", "Adrián", "Carlos", "Javier", "Ángel", "Raúl",
"Eduardo", "Nicolás", "Tomás", "Hugo", "Pablo", "Manuel", "José", "Cristian", "David", "Samuel",
"Rafael", "Óscar", "Esteban", "Rubén", "Francisco", "Héctor", "Iván", "Rodrigo", "Salvador", "Enrique",
"Martín", "Fabián", "Camilo", "Bruno", "Lucas", "Maximiliano", "Alonso", "Emmanuel", "Gonzalo", "Julio",
"Pedro", "Mariano", "Baltazar", "Simón", "Ezequiel", "Riccardo", "Marcos", "Gerardo", "César", "Lorenzo",
"Félix", "Damián", "Hernán", "Gustavo", "Vicente", "Ramón", "Emanuel", "Teo", "Sergio", "Federico",
"Guillermo", "Ivano", "Luciano", "Renato", "Felipe", "Jonathan", "Benjamin", "Raul", "Matías", "Jesús",
"Alfredo", "Cristóbal", "Ernesto", "Dario", "Alberto", "Julián", "Aníbal", "Agustín", "Romeo", "Leonel",
"Elias", "Ignacio", "Abel", "Mauricio", "Nahuel", "Ulises", "Tobías", "Humberto", "Jonás", "Patricio"
};

const char NOMBRES_F[100][50]={"Isabella", "Camila", "Valentina", "Sofía", "Mariana", "Luciana", "Gabriela", "Victoria", "Andrea", "Fernanda",
"Carla", "Patricia", "Ximena", "Daniela", "Adriana", "Beatriz", "Clara", "Rocío", "Alicia", "Julieta",
"Verónica", "Paula", "Josefina", "Carmen", "Bianca", "Renata", "Luz", "Estefanía", "Miranda", "Natalia",
"Florencia", "Elena", "Romina", "Montserrat", "Alejandra", "Luisa", "Vanessa", "Rosa", "Silvia", "Lorena",
"Maite", "Irene", "Bárbara", "Rebeca", "Cristina", "Fabiola", "Diana", "Gloria", "Anabella", "Noelia",
"Celeste", "Milagros", "Emilia", "Tatiana", "Teresa", "Aurora", "Leticia", "Belén", "Guadalupe", "Rosario",
"Marisol", "Francisca", "Ángela", "Selena", "Micaela", "Tamara", "Carolina", "Graciela", "Samantha", "Ivanna",
"Antonella", "Melina", "Lourdes", "Regina", "Amalia", "Consuelo", "Juana", "Paloma", "Esperanza", "Estrella",
"Zoe", "Jimena", "Araceli", "Yesenia", "Liliana", "Susana", "Tania", "Sol", "Pilar", "Gabriella",
"Dalila", "Magdalena", "Viviana", "Raquel", "Violeta", "Yolanda", "Lidia", "Soledad", "Perla", "Maritza"
};

const char APELLIDOS[200][50]=
{"García", "Rodríguez", "Martínez", "López", "González", "Hernández", "Pérez", "Sánchez", "Ramírez", "Torres",
"Flores", "Rivera", "Gómez", "Díaz", "Mendoza", "Vargas", "Castillo", "Ortega", "Chávez", "Ramos",
"Morales", "Guerrero", "Delgado", "Reyes", "Cruz", "Romero", "Vázquez", "Fuentes", "Arias", "Pineda",
"Carrillo", "Navarro", "Bautista", "Silva", "Serrano", "Rosales", "Cortez", "Escobar", "Valenzuela", "Jiménez",
"Mejía", "Salinas", "Montoya", "Trujillo", "Suárez", "Padilla", "Aguilar", "Campos", "Sandoval", "Luna",
"Ríos", "Peña", "Maldonado", "Cabrera", "Velázquez", "Esparza", "Quintero", "Hidalgo", "Figueroa", "Santos",
"Acosta", "Peralta", "Zamora", "Valverde", "Nieto", "Medina", "Castañeda", "Pacheco", "Santana", "Tovar",
"Tapia", "Avila", "Correa", "Cisneros", "Solano", "Gallegos", "Bermúdez", "Moya", "Escamilla", "Landa",
"Castro", "Valencia", "Alvarado", "Herrera", "Cruz", "Izquierdo", "Rio", "Salazar", "Muñoz", "Juárez",
"Domínguez", "Beltrán", "León", "Rojas", "Barajas", "Palacios", "Arroyo", "Villegas", "Cano", "Guevara",
"Smith", "Johnson", "Williams", "Brown", "Miller", "Davis", "Wilson", "Anderson", "Taylor", "Thomas",
"Moore", "Jackson", "White", "Harris", "Martin", "Thompson", "Clark", "Lewis", "Walker", "Hall",
"Allen", "Young", "King", "Wright", "Scott", "Green", "Adams", "Baker", "Carter", "Mitchell",
"Perez", "Evans", "Roberts", "Stewart", "Morris", "Nguyen", "Murphy", "Rivera", "Cook", "Rogers",
"Foster", "Gonzales", "Bryant", "Russell", "Griffin", "Hayes", "Patel", "Kim", "Simmons", "Powell",
"Bennett", "Wood", "Hughes", "Brooks", "Kelly", "Price", "Sanders", "Ross", "Coleman", "Jenkins",
"Perry", "Long", "Howard", "Fisher", "Garcia", "Cooper", "Richardson", "Cox", "Ward", "Torres",
"Peterson", "Gray", "Ramirez", "James", "Watson", "Brooks", "Kelly", "Barnes", "Bishop", "Ford",
"Chapman", "Lowe", "Fowler", "Hampton", "Parks", "Dixon", "Henderson", "Bush", "Gilbert", "Dean",
"Ortiz", "Soto", "Ponce", "Cervantes", "Molina", "Miranda", "Vega", "Ibarra", "Méndez", "Salgado"
};
