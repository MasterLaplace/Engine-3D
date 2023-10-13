# ME : <p align="center">**Collision**</p>

## Table of Contents :

- [**I. Introduction**](#introduction)

    1. Briefly describe the purpose of the project and the problem it aims to solve

- [**II. Overview of the Collision Detection and Response**](#overview)

    1. Explain the difference between collision detection and collision response
    2. Describe the approach that will be used for each

- [**III. Mesh Preprocessing**](#mesh)

    1. Discuss how the mesh of triangles will be prepared for collision detection using BVH
    2. Explain how the mesh will be subdivided into smaller bounding volumes, and how the BVH hierarchy will be constructed

- [**IV. Player Shape Representation**](#player)

    1. Describe how the player shape will be represented as an ellipsoid
    2. Explain the advantages of using an ellipsoid as the player shape

- [**V. Collision Detection**](#detection)

    1. Discuss the triangle-ellipsoid intersection test used to detect collisions between the player shape and the mesh
    2. Explain how the BVH structure will be used to improve the efficiency of the collision detection

- [**VI. Collision Response**](#response)

    1. Describe the sphere sweeping technique used to adjust the position or velocity of the player shape to prevent it from intersecting with the mesh
    2. Explain how the collision response will be implemented to ensure that it is accurate and efficient

- [**VII. Optimization Techniques**](#optimization)

    1. Discuss the use of multi-threading to improve performance
    2. Explain how the project will be optimized to ensure that it meets the performance and accuracy requirements

- [**VIII. Conclusion**](#conclusion)

    1. Summarize the main points of the project and how they address the problem at hand
    2. Provide a brief overview of any future work that could be done to further improve the collision detection and response system.

---

<div id='introduction'/>

### <p align="center">**I. Introduction**</p></br>

#### **1. Briefly describe the purpose of the project and the problem it aims to solve**
</br>

Collisions between objects have been a fundamental problem in physics and engineering for centuries. In the early days of mechanics, understanding the causes and effects of collisions was critical for designing machines and structures that could withstand impact forces. As technology progressed, the study of collisions expanded to fields such as automotive engineering, where the ability to predict and prevent collisions is essential for ensuring safety on the roads.

In the realm of computer engineering, collision detection and response have become crucial for a wide variety of applications, such as video games, virtual reality, and simulation environments. These applications require the ability to accurately detect collisions between objects in real-time, and respond to those collisions with appropriate physical interactions.

The problem of collision detection and response is a challenging one because it involves determining whether two objects are intersecting in 3D space, and then calculating the correct physical response to that intersection. This requires a high degree of computational precision, as even small errors in the collision detection and response can result in significant visual artifacts or physical inaccuracies.

The purpose of this project is to develop a collision engineering system that provides accurate and efficient collision detection and response for a low-resolution mesh of triangles and a player bound shape represented as an ellipsoid. The project aims to address the challenges of collision detection and response in a computationally efficient manner, while still providing a high degree of accuracy and precision.

---

<div id='overview'/>

### <p align="center">**II. Overview of the Collision Detection and Response**</p></br>

#### **1. Explain the difference between collision detection and collision response**
</br>

In the early days of collision engineering, the focus was primarily on collision detection. The goal was to determine whether two objects were colliding in 3D space. Early techniques for collision detection relied on simple geometric shapes, such as spheres or boxes, to represent objects. Collision detection algorithms would compare the positions and sizes of these shapes to determine whether they intersected in 3D space.

As technology and computational power progressed, the focus of collision engineering shifted to collision response. Collision response involves determining how two colliding objects should interact physically. This can include calculating the resulting forces, velocities, and movements of the objects involved in the collision.

The difference between collision detection and collision response can be thought of as the difference between identifying a problem and solving it. Collision detection identifies when a collision occurs, while collision response determines how to resolve that collision in a physically accurate and visually pleasing manner.

Today, collision detection and response are critical components of many applications, including video games, virtual reality, and simulation environments. The challenge of collision engineering is to provide accurate and efficient collision detection and response, while still maintaining a high degree of visual and physical realism. This requires a deep understanding of physics, geometry, and computational methods, as well as a keen eye for visual detail and user experience.
</br></br>

#### **2. Describe the approach that will be used for each**
</br>

Collision detection has historically been tackled using a variety of geometric methods. Early techniques relied on bounding volumes, such as spheres or boxes, to represent the objects being tested for collision. As computational power increased, more advanced algorithms were developed that used more complex shapes to represent the objects being tested.

In the realm of computer graphics, one popular approach for collision detection has been the use of mesh-based collision detection. This approach involves representing the objects as meshes of triangles, and then testing for collisions by comparing the positions and orientations of the triangles in 3D space. Mesh-based collision detection can be highly accurate, but it can also be computationally expensive.

Collision response has traditionally been more challenging to tackle than collision detection. One of the earliest approaches for collision response was to simply apply a force to the colliding objects in the direction opposite of the collision normal. This approach is still used today in some applications, but it can lead to unrealistic or jarring movements of the colliding objects.

More advanced collision response techniques involve calculating the forces and torques that result from the collision, and then integrating those forces and torques into the physics simulation of the objects. This requires a deep understanding of physics and mechanics, as well as a high degree of computational precision.

In recent years, machine learning and other artificial intelligence techniques have been used to tackle the challenges of collision detection and response. These techniques can provide highly accurate and efficient collision detection and response, but they can also be complex to implement and require significant computational resources.

---

<div id='mesh'/>

### <p align="center">**III. Mesh Preprocessing**</p></br>

#### **1. Discuss how the mesh of triangles will be prepared for collision detection using BVH**
</br>

Bounding volume hierarchies have been used for collision detection in computer graphics and simulation for several decades. The basic idea behind a BVH is to create a hierarchical structure of bounding volumes that enclose subsets of the objects being tested for collision. Each level of the hierarchy subdivides the objects into smaller and smaller subsets, until each subset contains a small enough number of objects that they can be compared for collisions efficiently.

In the context of collision detection with a mesh of triangles, the first step is to prepare the mesh for use with BVH. This involves breaking the mesh down into a set of individual triangles and creating bounding volumes around each triangle. The bounding volumes can be simple geometric shapes, such as spheres or boxes, or they can be more complex shapes that are specifically designed to fit the shape of the triangle.

Once the bounding volumes have been created, they can be organized into a BVH structure. There are several different algorithms for constructing BVH structures, but they all involve recursively subdividing the bounding volumes into smaller and smaller subsets until each subset contains a small enough number of triangles to be compared for collision efficiently.

One of the earliest BVH algorithms was the bounding interval hierarchy (BIH), which was introduced in the late 1990s. Since then, several other BVH algorithms have been developed, including the axis-aligned bounding box hierarchy (AABB) and the oriented bounding box hierarchy (OBB). These algorithms have been refined and optimized over the years to improve their performance and accuracy.

Today, BVH structures are used in a wide variety of applications, including video games, computer-aided design, and scientific simulations. They provide a highly efficient and accurate method for collision detection with complex 3D models, such as meshes of triangles.
</br></br>

#### **2. Describe the approach that will be used for each**
</br>

The process of subdividing the mesh of triangles into smaller bounding volumes and constructing a BVH hierarchy typically involves a recursive algorithm that subdivides the mesh into smaller and smaller volumes until each volume contains a small enough number of triangles to be tested efficiently for collisions. One of the earliest algorithms for constructing a BVH hierarchy in this way was the bounding interval hierarchy (BIH), which was introduced in the late 1990s.

Let's consider a simple example of a mesh of triangles representing a cube. To create the BVH hierarchy, we start by creating a bounding volume that encloses the entire cube. This bounding volume might be a simple box or sphere that fits around the cube. We then subdivide this volume into two smaller volumes, one for each half of the cube. Each of these smaller volumes is then subdivided again, into four even smaller volumes, and so on.

At each step of the subdivision process, we need to decide how to split the current volume into smaller volumes. One common approach is to use an axis-aligned bounding box hierarchy (AABB), which involves splitting the current volume into two smaller volumes along one of the major axes of the coordinate system. For example, if we have an AABB that encloses the entire cube, we might split it into two smaller AABBs, one that encloses the left half of the cube and one that encloses the right half.

Once we have subdivided the mesh into a set of smaller bounding volumes, we can construct the BVH hierarchy by creating a tree structure that organizes the volumes in a hierarchical manner. At the top of the tree is the bounding volume that encloses the entire mesh, and at each subsequent level of the tree, we have smaller and smaller volumes that enclose subsets of the mesh. Each node in the tree contains a reference to the bounding volume that it represents, as well as references to its child nodes.

The BVH hierarchy can be traversed efficiently using a variety of algorithms, such as the recursive top-down traversal algorithm or the stack-based iterative traversal algorithm. These algorithms allow us to quickly test for collisions between the mesh and other objects in the simulation.
