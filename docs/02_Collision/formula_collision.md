prouver que la moyenne de tout les points d'un triangle est le centre de gravité du triangle et surtout que le maximum et le minimum d'une liste de triangles contient n'importe qu'elle centre de gravité du triangle donné.

$$
\mathbf{\vec{T}}_{\min} \leq \overline{\vec{T}_n} \leq \mathbf{\vec{T}}_{\max}
$$

is sphere-triangle collision

$$
\vec{TN} = \frac{(\vec{T}_1 - \vec{T}_0) \times (\vec{T}_2 - \vec{T}_0)}{\sqrt{(\vec{T}_1 - \vec{T}_0) \times (\vec{T}_2 - \vec{T}_0) \cdot (\vec{T}_1 - \vec{T}_0) \times (\vec{T}_2 - \vec{T}_0)}} \\
SD = (\vec{C} - \vec{T}_0) \cdot \vec{TN} \\
\left| SD \right| < R
$$

resolve sphere-triangle collidion

$$
\vec{V} = (\vec{T}_1 - \vec{T}_0) \times (\vec{T}_2 - \vec{T}_0) \\
\vec{TN} = \frac{\vec{V}}{\sqrt{\vec{V} \cdot \vec{V}}} \\
SD = (\vec{C} - \vec{T}_0) \cdot \vec{TN} \\

if \left| SD \right| < R \\
    PD = R - \left| SD \right| \\
    if SD < 0 \\
        \vec{C} = \vec{C} - \vec{TN} \times PD \\
    else \\
        \vec{C} = \vec{C} + \vec{TN} \times PD \\
$$
