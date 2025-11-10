
🌀 **Flood Relief Camp and Resource Allocation System**


📘 ***Overview***

This project is a C-based Flood Relief Management System designed to efficiently manage relief operations during natural disasters.
It implements two core Data Structures:

Queue (Linear): used to manage relief requests in FIFO order.

Graph (Non-linear): used to represent areas and their connectivity for efficient resource delivery.

The system enables adding areas, connecting them, registering camps, maintaining stock, and allocating resources.

🧩 ***Functionalities***

1)Add Areas and Connectivity

2)Add new areas (nodes) and establish connections (edges) between them.

3)Simulates real-world connectivity for resource delivery.

4)Register Camps and Available Resources

5)Each camp maintains available stock of relief materials.

6)Stock is stored and managed using a queue.

7)Enqueue Relief Requests

8)Requests are added in FIFO order to ensure fairness.

9)Allocate Resources and Update Stock

10)Packages are dequeued and delivered to the required areas.

11)Graph nodes are updated from Pending to Delivered.

⚙️ ***Data Structures Used***

Data Structure	Type	Purpose
Queue	Linear	Handles relief package requests in FIFO order
Graph (Adjacency Matrix)	Non-linear	Represents areas and their connections for delivery planning

🧠 ***File Structure***

flood_relief/

├── main.c        → main driver file (menu, user interface)

├── flood.h       → header file (structure & function declarations)

├── queue.c       → queue implementation (managing relief packages)

├── graph.c       → graph implementation (areas & connectivity)

└── README.md     → project documentation

🧩 ***How It Works***

->Initialize the System

->Creates an empty graph and queue.

->Add Areas

->Add affected areas using addArea().

->Add Connectivity

->Connect two areas using addConnection() (bidirectional).

->Manage Stock

->Add packages to inventory using enqueue().

->Remove packages for delivery using dequeue().

->Mark Deliveries

->Once resources reach an area, mark it as Delivered in the graph.

🧪 ***Menu (CLI Interface)***

==== FLOOD RELIEF MANAGEMENT ====

1. Add stock to inventory
2. Remove stock for transport
3. Add area
4. Delete area
5. Add connectivity
6. Display graph
7. Mark area as delivered
8. Display stock
0. Exit

⚙️ ***How to Compile and Run***

*On Linux / Mac:*


gcc main.c graph.c queue.c -o flood_relief
./flood_relief




*On Windows (CMD or PowerShell):*



gcc main.c graph.c queue.c -o flood_relief.exe
flood_relief



💡 ***Example Workflow***

Add areas: AreaA, AreaB, AreaC

Connect: AreaA ↔ AreaB, AreaB ↔ AreaC

Add 10 packages to inventory

Deliver 3 packages and mark AreaA as delivered

Display graph → shows AreaA marked as Delivered

👩‍💻 ***Team Members***

Shreya Patil – PES2UG24CS484

Shreya Shenoy – PES2UG24CS487

Shrungashree K R – PES2UG24CS497

📚 ***Key Learning Outcomes***

Implemented Queue and Graph in a real-world simulation scenario.

Practiced modular programming using multiple C source files.

Understood FIFO processing and Graph traversal concepts.


Strengthened skills in data structure design and clean code organization.

