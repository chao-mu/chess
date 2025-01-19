#!/usr/bin/env python

from enum import Enum
from typing import Optional
import click

from selenium import webdriver
from selenium.webdriver.firefox.options import Options
from selenium.webdriver.common.by import By

from dataclasses import dataclass, field
import hashlib
import time

from selenium.webdriver.remote.webelement import WebElement


def find_button(browser):
    return browser.find_elements(By.TAG_NAME, "button")


def find_a(browser):
    return browser.find_elements(By.TAG_NAME, "a")


def get_xpath(elm):
    """
    https://stackoverflow.com/a/75076502
    """
    e = elm
    xpath = elm.tag_name
    while e.tag_name != "html":
        e = e.find_element(By.XPATH, "..")
        neighbours = e.find_elements(By.XPATH, "../" + e.tag_name)
        level = e.tag_name
        if len(neighbours) > 1:
            level += "[" + str(neighbours.index(e) + 1) + "]"
        xpath = level + "/" + xpath
    return "/" + xpath


DOMPath = str
Halts = bool


class Action(Enum):
    NONE = 0
    CLICK = 1


@dataclass
class Step:
    path: DOMPath
    action: Action


@dataclass
class ElementSet:
    values: dict[DOMPath, WebElement] = field(default_factory=dict)


@dataclass
class Journey:
    to_here: list[Step]
    continuations: list[Step]
    url: str


def get_path(el: WebElement):
    return get_xpath(el)


def get_continuations(driver) -> list[Step]:
    continuations: list[Step] = []
    for el in find_a(driver):
        path = get_path(el)
        continuations.append(Step(path=path, action=Action.CLICK))

    return continuations


def continue_journey(driver, journey: Optional[Journey]):
    if journey is None:
        continuations = get_continuations(driver)
        baseline_url = driver.current_url
        to_here = []
    else:
        continuations = journey.continuations
        baseline_url = journey.url
        to_here = journey.to_here

    for step in continuations:
        driver.get(baseline_url)
        if step.action == Action.CLICK:
            el = driver.find_element(By.XPATH, step.path)
            el.click()
        else:
            raise NotImplementedError()

        time.sleep(5)

        file_path = hashlib.md5(step.path.encode()).hexdigest()
        driver.save_full_page_screenshot(file_path + ".png")

        yield Journey(
            to_here=to_here + [step],
            continuations=get_continuations(driver),
            url=driver.current_url,
        )


@click.command()
@click.argument("url")
def main(url: str):
    options = Options()
    options.add_argument("--headless")
    driver = webdriver.Firefox(options=options)
    driver.get(url)
    driver.implicitly_wait(5)

    journey = Journey(
        to_here=[], continuations=get_continuations(driver), url=driver.current_url
    )

    for _ in continue_journey(driver, journey):
        pass


if __name__ == "__main__":
    main()
