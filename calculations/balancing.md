### Working in polar coordinates
#### Important note:
$$
\hat{r} = \hat{x}\cos\theta + \hat{y}sin\theta
$$$$
\hat{e} = -\hat{x}\sin\theta + \hat{y}cos\theta
$$$$
\frac{d\hat{r}}{d\theta} = \hat{e}
$$$$
\frac{d\hat{e}}{d\theta} = -\hat{r}
$$

#### Deriving equation of motion:
##### Vector point in polar coordinates:
$$
\vec{P} = r\hat{r}
$$

##### First derivative:
$$
\dot{\vec{P}} = \dot{r}\hat{r} + r\frac{d\hat{r}}{dt}
$$$$
\dot{\vec{P}} = \dot{r}\hat{r} + r\dot{\theta}\frac{d\hat{r}}{d\theta}
$$$$
\dot{\vec{P}} = \dot{r}\hat{r} + r\dot{\theta}\hat{e}
$$

##### Second derivative:
$$
\ddot{\vec{P}} = \ddot{r}\hat{r} +\dot{r}\frac{d\hat{r}}{dt} + \dot{r}\dot{\theta}\hat{e} + r\ddot{\theta}\hat{e} + r\dot{\theta}\frac{d\hat{e}}{dt}
$$$$
\ddot{\vec{P}} = \ddot{r}\hat{r} + \dot{r}\dot{\theta}\hat{e} + \dot{r}\dot{\theta}\hat{e} + r\ddot{\theta}\hat{e} + r\dot{\theta}\dot{\theta}\frac{d\hat{e}}{d\theta}
$$$$
\ddot{\vec{P}} = \ddot{r}\hat{r} + 2\dot{r}\dot{\theta}\hat{e} + r\ddot{\theta}\hat{e} - r\dot{\theta}^2\hat{r}
$$$$
\ddot{\vec{P}} = [\ddot{r} - r\dot{\theta}^2]\hat{r} + [2\dot{r}\dot{\theta} + r\ddot{\theta}]\hat{e}
$$

### Pendulum in 2D:
A mass $m$ at the end of a sturdy rod of length $r$ at angle $\theta$ will be released.
I will assume that the components of force along the tangential component $\hat{e}$ will be from the mass

$$
mg\sin{\theta} \approx mg\theta \text{ [small angle approximation]}
$$
and a constant damping force $k$ proportional to the tangential velocity $v_{tangent} = r\dot{\theta}$ angular velocity
$$
k * v_{tangential}
$$$$
kr\dot{\theta}
$$
This means that the pendulum experiences a "dropping" force along $\hat{e}$ of
$$
\vec{F}_{falling} = [mg\theta - k\dot{\theta}]\hat{e}
$$

### Balancing Robot
Using the **second derivative** derived earlier

$$
\ddot{\vec{P}} = [\ddot{r} - r\dot{\theta}^2]\hat{r} + [2\dot{r}\dot{\theta} + r\ddot{\theta}]\hat{e}
$$
With $\ddot{r} = \dot{r} = 0$ (a fixed rod length) it can be seen that the equation of motion along $\hat{e}$ will be equal to
$$
\vec{a} = r\ddot{\theta}\hat{e}
$$$$
\therefore \vec{F}_{motion} = m\vec{a} = mr\ddot{\theta}
$$
Having the elegoo-tumbller $\vec{F}_{motion}$ counteract $\vec{F}_{falling}$ it can be seen
$$
mr\ddot{\theta} = mg\theta - kr\dot{\theta}
$$$$
\therefore \ddot{\theta} = \frac{g}{r}\theta - \frac{k}{m}\dot{\theta}
$$$$
\therefore \vec{a}_{wheels} = k_1\theta + k_2\dot{\theta}
$$

Where $k_1$ and $k_2$ are constants to be determined through testing. This equation will be used as the wheel acceleration control algorithm and through measuring the angle of inclination $\theta$ and the angular velocity $\dot{\theta}$ this should be capable of balancing the vehicle
