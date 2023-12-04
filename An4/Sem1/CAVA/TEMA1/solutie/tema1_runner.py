# typer e un argparse pe steroizi
import typer

app = typer.Typer()


@app.command()
def task1():
    pass


@app.command()
def task2():
    pass


@app.command()
def task3():
    pass


if __name__ == "__main__":
    app()
