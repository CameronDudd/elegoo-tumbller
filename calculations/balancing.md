### Balancing Robot
TODO (cameron): Finish calculation refactor
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
