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
