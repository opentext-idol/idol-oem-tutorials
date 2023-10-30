"""
Intelligently summarize text using an OEM-licensed IDOL Content Server:
$ python summarize_text_oem.py
"""
import context as aci
import xml.etree.ElementTree as ET

wiki_article = """
Artificial intelligence (AI) is the intelligence of machines or software, as opposed to the intelligence of humans or animals. It is also the field of study in computer science that develops and studies intelligent machines. "AI" may also refer to the machines themselves.

AI technology is widely used throughout industry, government and science. Some high-profile applications are: advanced web search engines (e.g., Google Search), recommendation systems (used by YouTube, Amazon, and Netflix), understanding human speech (such as Siri and Alexa), self-driving cars (e.g., Waymo), generative or creative tools (ChatGPT and AI art), and competing at the highest level in strategic games (such as chess and Go).

Artificial intelligence was founded as an academic discipline in 1956. The field went through multiple cycles of optimism followed by disappointment and loss of funding, but after 2012, when deep learning surpassed all previous AI techniques, there was a vast increase in funding and interest.

The various sub-fields of AI research are centered around particular goals and the use of particular tools. The traditional goals of AI research include reasoning, knowledge representation, planning, learning, natural language processing, perception, and support for robotics. General intelligence (the ability to solve an arbitrary problem) is among the field's long-term goals. To solve these problems, AI researchers have adapted and integrated a wide range of problem-solving techniques, including search and mathematical optimization, formal logic, artificial neural networks, and methods based on statistics, operations research, and economics. AI also draws upon psychology, linguistics, philosophy, neuroscience and many other fields.
"""
# -- https://en.wikipedia.org/wiki/Artificial_intelligence
n_sentences = 2

response = aci.client.call(
  encryption_key="<REPLACE_WITH_MY_LONG_KEY_STRING>",
  hostname="127.0.0.1", 
  port=9100, 
  aci_action="Summarize",
  aci_params = {
    "Text": wiki_article,
    "Summary": "Concept",
    "Sentences": n_sentences
  }
)
# print(response)

root = ET.fromstring(response)
namespaces = {'autn': 'http://schemas.autonomy.com/aci/'}

# print("Original:")
# print(wiki_article)

# print(f"{n_sentences}-sentence summary:")
print(root.find(".//autn:summary", namespaces).text)
