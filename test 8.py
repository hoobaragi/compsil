# 필요한 라이브러리 가져오기
from transformers import pipeline

# 텍스트 데이터 정의
text = """The South Korean general appointed as the commander of President
Yoon Suk Yeol’s short-lived declaration of martial law learned of the move
only when Mr. Yoon announced it on television, the general told lawmakers
during hearings on Thursday. Despite his position, the general, Park
An-su, told a parliamentary committee that he also did not know who
ordered troops to move in on the National Assembly in an attempt to cordon
it off. During his testimony, the deputy defense minister, Kim Seon-ho,
said that the defense minister had ordered the troops in. Mr. Kim said
that he had opposed the mobilization. The defense minister, Kim Yong-hyun,
resigned Thursday before the hearings and did not take part. The hearings
were an inquiry into why martial law was declared for several hours on
Tuesday night. Mr. Yoon’s extraordinary move plunged the country into a
political crisis, caused widespread anger and drove thousands of
protesters to the streets."""

# 텍스트 분류 파이프라인 초기화
text_classification_pipeline = pipeline("text-classification")

# 텍스트 분류 수행
classification_results = text_classification_pipeline(text)
print("텍스트 분류 결과:", classification_results)

# 개체명 인식 파이프라인 초기화
ner_pipeline = pipeline("ner", aggregation_strategy="simple")

# 개체명 인식 수행
ner_results = ner_pipeline(text)
print("개체명 인식 결과:", ner_results)

# 질문 답변 파이프라인 초기화
qa_pipeline = pipeline("question-answering")

# 질문 정의
questions = [
    "Who appointed the commander?",
    "What was declared on Tuesday night?",
    "Who resigned before the hearings?"
]

# 질문에 대한 답변 수행
for question in questions:
    result = qa_pipeline(question=question, context=text)
    print(f"질문: {question}\n답변: {result['answer']}\n")

# 요약 파이프라인 초기화
summarization_pipeline = pipeline("summarization")

# 텍스트 요약 수행
summary_results = summarization_pipeline(text)
print("요약:", summary_results[0]['summary_text'])
